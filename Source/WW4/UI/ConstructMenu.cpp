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
				Item->bUseCount = false;
				UGP_Building->AddChildToUniformGrid(Item, TypeNumMap[Type] / 2, TypeNumMap[Type] % 2);
				break;
			case EContructItemType::ECT_Vehicle:
				Item->bNeedDeploy = false;
				Item->bUseCount = true;
				UGP_Vehicle->AddChildToUniformGrid(Item, TypeNumMap[Type] / 2, TypeNumMap[Type] % 2);
				break;
			default:
				break;
			}
			TypeNumMap[Type] += 1;
			Item->OnConstrcutItemClickedHandle.AddDynamic(this, &UConstructMenu::OnConstructItemClick);
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
			if (Item)
			{
				if (bEnable)
				{
					if (Item->Count < 0)
					{
						Item->SetState(EConstructItemState::ECS_Normal);
						if (Item->ItemInfo.ItemID == ItemInfo.ItemID)
						{
							Item->EnableMask1(false);
						}
					}
				}
				else if(Item->ItemInfo.ItemID != ItemInfo.ItemID)
				{
					Item->SetState(EConstructItemState::ECS_Disabled);
				}
			}
		}
		break;
	case EContructItemType::ECT_Vehicle:
		for (auto* ItemWidget : UGP_Vehicle->GetAllChildren())
		{
			UConstructItem* Item = Cast<UConstructItem>(ItemWidget);
			if (Item)
			{
				if (bEnable)
				{
					if (Item->Count < 0)
					{
						Item->SetState(EConstructItemState::ECS_Normal);
					}
				}
				else if (Item->ItemInfo.ItemID != ItemInfo.ItemID)
				{
					Item->SetState(EConstructItemState::ECS_Disabled);
				}
			}
		}
		break;
	default:
		break;
	}
}

void UConstructMenu::UpdateItemProgress(const FItemProductionInfoBase& Info, float Ratio)
{
	if (ItemInfoMap.Contains(Info))
	{
		ItemInfoMap[Info]->UpdateProgress(Ratio);
	}
}


void UConstructMenu::OnConstructItemClick(const FItemProductionInfoBase& ItemInfo, bool bReady)
{
	AWW4PlayerController* PC = UWW4CommonFunctionLibrary::GetWW4PlayerController(GetWorld());

	if (bReady)
	{
		if (ItemInfo.ItemType == EContructItemType::ECT_Building)
		{
			if (ConstructorcClass)
			{
				ABuildingConstructor* Constructor = GetWorld()->SpawnActor<ABuildingConstructor>(ConstructorcClass, FTransform());
				Constructor->UnitID = ItemInfo.ItemID;
				Constructor->InitCell();
			}
		}
		else if (PC && ItemInfo.ItemType == EContructItemType::ECT_Vehicle)
		{
			if (PC->PlayerBaseComponent && PC->PlayerBaseComponent->CurrentVehicleFactory)
			{
				PC->PlayerBaseComponent->ServerSpawnUnit(
					ItemInfo,
					PC->PlayerBaseComponent->GetWW4PlayerID(),
					PC->PlayerBaseComponent->CurrentVehicleFactory->GetSpawnTransform(),
					PC->PlayerBaseComponent->CurrentVehicleFactory
				);
			}
			AWW4HUD* HUD = Cast<AWW4HUD>(PC->GetHUD());
			if (HUD)
			{
				HUD->RefreshItemGroupState(ItemInfo, true);
			}
		}
	}
	else if(PC)
	{
		PC->EconomyComponent->AddOrRemoveCostItem(ItemInfo, true);
		AWW4HUD* HUD = Cast<AWW4HUD>(PC->GetHUD());
		if (HUD)
		{
			HUD->RefreshItemGroupState(ItemInfo, false);
		}
	}
}