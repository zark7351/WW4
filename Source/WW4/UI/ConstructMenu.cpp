// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructMenu.h"
#include "Components/UniformGridPanel.h"
#include "WW4/Building/BuildingBase.h"
#include "ConstructItem.h"
#include "components/Button.h"
#include "WW4/BuildingConstructor.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4/Unit/UnitBase.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"

UConstructMenu::UConstructMenu(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> BuildingDatatableFinder(TEXT("Datatable'/Game/WW4/Datatable/DT_BuildingInfo.DT_BuildingInfo'"));
	if (BuildingDatatableFinder.Succeeded())
	{
		BuildingInfo = BuildingDatatableFinder.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to load BuildingInfo datatable!"));
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> VehicleDatatableFinder(TEXT("Datatable'/Game/WW4/Datatable/DT_VehicleInfo.DT_VehicleInfo'"));
	if (VehicleDatatableFinder.Succeeded())
	{
		VehicleInfo = VehicleDatatableFinder.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to load VehicleInfo datatable!"));
	}
}

void UConstructMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (UGP_Building && BuildingInfo)
	{
		InitConstructionList(UGP_Building, BuildingInfo, EContructItemType::ECT_Building);
	}
	if (UGP_Vehicle && VehicleInfo)
	{
		InitConstructionList(UGP_Vehicle, VehicleInfo, EContructItemType::ECT_Vehicle);
	}
	
}

void UConstructMenu::NativeConstruct()
{
	Super::NativeConstruct();

}

void UConstructMenu::InitConstructionList(UUniformGridPanel* UniformGridPanel, UDataTable* Datatable, EContructItemType ItemType)
{
	if (UniformGridPanel && Datatable)
	{
		TArray<FItemProductionInfoBase*> ItemProductionInfo;
		Datatable->GetAllRows("", ItemProductionInfo);
		UClass* ItemClass = LoadClass<UConstructItem>(nullptr, TEXT("/Game/WW4/UI/WBP_ConstructItem.WBP_ConstructItem_C"));
		for (int32 i = 0; i < ItemProductionInfo.Num(); i++)
		{
			if (ItemProductionInfo[i])
			{
				UConstructItem* Item = CreateWidget<UConstructItem>(GetWorld(), ItemClass);
				if (Item)
				{
					UniformGridPanel->AddChildToUniformGrid(Item, i / 2, i % 2);
					Item->OnConstrcutItemClickedHandle.AddDynamic(this, &UConstructMenu::OnConstructItemClick);
					Item->ItemInfo = *(ItemProductionInfo[i]);
				}
			}
		}
	}
}

//PRAGMA_DISABLE_OPTIMIZATION

void UConstructMenu::OnConstructItemClick(const FItemProductionInfoBase& ItemInfo)
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
	else if (ItemInfo.ItemType == EContructItemType::ECT_Vehicle)
	{
		AUnitManager* UnitManager = UWW4CommonFunctionLibrary::GetUnitManager(GetWorld());
		if (UnitManager)
		{
			UnitManager->SpawnVehicle(EFaction::EF_RedTeam, ItemInfo.ItemClass);
		}
		
	}

}

//PRAGMA_ENABLE_OPTIMIZATION