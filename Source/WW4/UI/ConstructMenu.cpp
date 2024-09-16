// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructMenu.h"
#include "Components/UniformGridPanel.h"
#include "WW4/Building/BuildingBase.h"
#include "ConstructItem.h"
#include "components/Button.h"
#include "WW4/Other/BuildingConstructor.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4/Unit/UnitBase.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Core/WW4PlayerController.h"
#include "WW4/Component/PlayerEconomyComponent.h"
#include "WW4/Component/PlayerBaseComponent.h"
#include "WW4/Core/WW4HUD.h"
#include "WW4/Building/UnitFactoryBase.h"

UConstructMenu::UConstructMenu(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

void UConstructMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UConstructMenu::NativeConstruct()
{
	Super::NativeConstruct();

}

void UConstructMenu::InitAllConstructionList(const TArray<FItemProductionInfoBase>& Items)
{
	//TODO:需要优化，不要每次全部重新创建
	ItemInfoMap.Empty();
	UGP_Building->ClearChildren();
	UGP_Vehicle->ClearChildren();
	if (!ConstructItemClass)	return;
	TMap<EContructItemType, int32>TypeNumMap;
	for (int32 i = 0; i < Items.Num(); i++)
	{
		UConstructItem* Item = CreateWidget<UConstructItem>(GetWorld(), ConstructItemClass);
		if (Item)
		{
			ItemInfoMap.Add(Items[i], Item);
			EContructItemType Type = Items[i].ItemType;
			if (!TypeNumMap.Contains(Type))
			{
				TypeNumMap.Add(Type, 0);
			}
			switch (Type)
			{
			case EContructItemType::ECT_Building:
				Item->bNeedDeploy = true;
				Item->bMultiBuild = false;
				UGP_Building->AddChildToUniformGrid(Item, TypeNumMap[Type] / 2, TypeNumMap[Type] % 2);
				break;
			case EContructItemType::ECT_Vehicle:
				Item->bNeedDeploy = false;
				Item->bMultiBuild = true;
				UGP_Vehicle->AddChildToUniformGrid(Item, TypeNumMap[Type] / 2, TypeNumMap[Type] % 2);
				break;
			default:
				break;
			}
			TypeNumMap[Type] += 1;
			Item->OnConstrcutItemClicked.AddDynamic(this, &UConstructMenu::OnConstructItemClick);
			Item->OnUnitReady.AddDynamic(this, &UConstructMenu::OnUnitReady);
			Item->ItemInfo = (Items[i]);
		}
	}
}

void UConstructMenu::RefreshGroupState(const FItemProductionInfoBase& ItemInfo, bool bEnable)
{
	switch (ItemInfo.ItemType)
	{
	case EContructItemType::ECT_Building:
		for (auto* ItemWidget : UGP_Building->GetAllChildren())
		{
			UConstructItem* Item = Cast<UConstructItem>(ItemWidget);
			if (Item && Item->ItemInfo.ItemID != ItemInfo.ItemID)
			{
				Item->SetState(bEnable ? EConstructItemState::ECS_Normal : EConstructItemState::ECS_Disabled);
			}
			else if (Item && Item->ItemInfo.ItemID == ItemInfo.ItemID && Item->GetState() == EConstructItemState::ECS_Ready)
			{
				Item->SetState(EConstructItemState::ECS_Normal);
			}
		}
		break;
	case EContructItemType::ECT_Vehicle:
		for (auto* ItemWidget : UGP_Vehicle->GetAllChildren())
		{
			UConstructItem* Item = Cast<UConstructItem>(ItemWidget);
			if (Item && Item->ItemInfo.ItemID != ItemInfo.ItemID)
			{
				Item->SetState(bEnable ? EConstructItemState::ECS_Normal : EConstructItemState::ECS_Waiting);
			}
		}
		break;
	default:
		break;
	}
}

void UConstructMenu::UpdateItemProgress(const FItemProductionInfoBase& Info, float Ratio, bool bStart)
{
	if (ItemInfoMap.Contains(Info))
	{
		ItemInfoMap[Info]->UpdateProgress(Ratio, bStart);
	}
}


void UConstructMenu::OnConstructItemClick(const FItemProductionInfoBase& ItemInfo, EConstructOperationType Type)
{
	AWW4PlayerController* PC = UWW4CommonFunctionLibrary::GetWW4PlayerController(GetWorld());
	switch (Type)
	{
	case EConstructOperationType::Build:
		if (PC)
		{
			PC->EconomyComponent->AddCostItem(ItemInfo);
			RefreshGroupState(ItemInfo, false);
		}
		break;
	case EConstructOperationType::Deploy:
		if (ItemInfo.ItemType == EContructItemType::ECT_Building)
		{
			if (ConstructorcClass)
			{
				ABuildingConstructor* Constructor = GetWorld()->SpawnActor<ABuildingConstructor>(ConstructorcClass, FTransform());
				Constructor->UnitID = ItemInfo.ItemID;
				Constructor->InitCell();
			}
		}
		break;
	case EConstructOperationType::AddWaitList:
		WaitingItems.AddUnique(ItemInfo);
		break;
	case EConstructOperationType::RemoveWaitList:
		WaitingItems.Remove(ItemInfo);
		break;
	case EConstructOperationType::Cancele:
		if (PC)
		{
			PC->EconomyComponent->RemoveCostItem(ItemInfo, true);
			AddNextWaitingItem(ItemInfo, PC);
		}
		break;
	case EConstructOperationType::Return:
		if (PC)
		{
			PC->EconomyComponent->ReturnItemMoney(ItemInfo);
		}
		break;
	case EConstructOperationType::OnHold:
		if (PC)
		{
			PC->EconomyComponent->RemoveCostItem(ItemInfo, false);
		}
		break;
	case EConstructOperationType::Resume:
		if (PC)
		{
			PC->EconomyComponent->AddCostItem(ItemInfo);
		}
		break;
	default:
		break;
	}
}

void UConstructMenu::OnUnitReady(const FItemProductionInfoBase& ItemInfo, bool bIsLastOne)
{
	AWW4PlayerController* PC = UWW4CommonFunctionLibrary::GetWW4PlayerController(GetWorld());
	if (!PC)
	{
		return;
	}
	if (ItemInfo.ItemType == EContructItemType::ECT_Vehicle || ItemInfo.ItemType == EContructItemType::ECT_Infantry)
	{
		if (PC->PlayerBaseComponent && PC->PlayerBaseComponent->CurrentVehicleFactory)
		{
			PC->PlayerBaseComponent->ServerSpawnUnit(
				ItemInfo,
				PC->PlayerBaseComponent->WW4PlayerID,
				PC->PlayerBaseComponent->CurrentVehicleFactory->GetSpawnTransform(),
				PC->PlayerBaseComponent->CurrentVehicleFactory
			);
		}
		if (bIsLastOne)
		{
			if (AddNextWaitingItem(ItemInfo, PC)) return;
		}
	}
	else
	{
		RefreshGroupState(ItemInfo, true);
	}
}

bool UConstructMenu::AddNextWaitingItem(const FItemProductionInfoBase& ItemInfo, AWW4PlayerController* PC)
{
	EContructItemType Type = ItemInfo.ItemType;
	for (int32 i = 0; i < WaitingItems.Num(); i++)
	{
		if (WaitingItems[i].ItemType == Type)
		{
			PC->EconomyComponent->AddCostItem(WaitingItems[i]);
			ItemInfoMap[WaitingItems[i]]->SetState(EConstructItemState::ECS_Building);
			RefreshGroupState(WaitingItems[i], false);
			WaitingItems.RemoveAt(i);
			return true;
		}
	}
	RefreshGroupState(ItemInfo, true);
	return false;
}
