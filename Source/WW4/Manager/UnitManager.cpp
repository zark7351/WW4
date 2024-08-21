// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitManager.h"
#include "WW4/Building/UnitFactoryBase.h"
#include "WW4/Unit/UnitBase.h"
#include "WW4/Unit/Vehicle/VehicleBase.h"
#include "WW4/Building/BuildingBase.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WW4/Core/WW4GameModeBase.h"
#include "EngineUtils.h"


AUnitBase* UUnitManager::SpawnUnit(FItemProductionInfoBase ItemInfo, int32 InPlayerID, AUnitFactoryBase* SpawnBuilding)
{
	AUnitBase* Unit = nullptr;
	if (SpawnBuilding)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		Unit = GetWorld()->SpawnActor<AUnitBase>(ItemInfo.ItemClass, SpawnBuilding->GetSpawnTransform(),Params);
		if (Unit)
		{
			Unit->ItemInfo = ItemInfo;
			if (Units.Contains(InPlayerID))
			{
				Units[InPlayerID].Units.Add(FUnitInfoBase(Unit, InPlayerID));
			}
			else
			{
				Units.Add(InPlayerID, FUnitsInfo(Unit, InPlayerID));
			}
		}
	}
	return Unit;
}

AUnitBase* UUnitManager::SpawnUnit(FItemProductionInfoBase ItemInfo, int32 InPlayerID, const FTransform& Transform, ABuildingBase* OwnerBuilding)
{
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AUnitBase* Unit = GetWorld()->SpawnActor<AUnitBase>(ItemInfo.ItemClass , Transform, Params);
	if (Unit)
	{
		Unit->SetOwnerBuilding(OwnerBuilding);
		if (Units.Contains(InPlayerID))
		{
			Units[InPlayerID].Units.Add(FUnitInfoBase(Unit, InPlayerID));
		}
		else
		{
			Units.Add(InPlayerID, FUnitsInfo(Unit, InPlayerID));
		}
		Unit->OnInit();
	}
	return Unit;
}

bool UUnitManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return UKismetSystemLibrary::IsServer(Outer);
}

void UUnitManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CollectBuildingsAndUnits();
}

void UUnitManager::Deinitialize()
{
	Super::Deinitialize();
}

void UUnitManager::SpawnVehicle(FItemProductionInfoBase ItemInfo, int32 InPlayerID)
{
	if (CurrentVehicleFactory)
	{
		SpawnUnit(ItemInfo, InPlayerID, CurrentVehicleFactory);
	}
}

void UUnitManager::SetCurrentFactory(EContructItemType Type, AUnitFactoryBase* InFactory)
{
	switch (Type)
	{
	case EContructItemType::ECT_Building:
		CurrentVehicleFactory = InFactory;
		break;
	case EContructItemType::ECT_Infantry:
		CurrentInfantryFactory = InFactory;
		break;
	case EContructItemType::ECT_Vehicle:
		break;
	case EContructItemType::ECT_Max:
		break;
	default:
		break;
	}
}

void UUnitManager::SpawnBuilding(int32 InPlayerID, FName BuildingName, const FVector& Location, const FRotator& Rotation)
{
	if (BuildingGridInfo)
	{
		FItemProductionInfoBase* Row = BuildingGridInfo->FindRow<FItemProductionInfoBase>(BuildingName, "");
		if (Row && Row->ItemClass)
		{
			ABuildingBase* Building = GetWorld()->SpawnActorDeferred<ABuildingBase>(Row->ItemClass, FTransform(Rotation, Location),nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			if (Building)
			{
				Building->ItemInfo = *Row;
				if (Buildings.Contains(InPlayerID))
				{
					Buildings[InPlayerID].Buildings.Add(Building);
				}
				else
				{
					Buildings.Add(InPlayerID, Building);
				}
				Building->FinishSpawning(FTransform(Rotation, Location));
			}
		}
	}
}

void UUnitManager::OnBuildingDestroy(int32 InPlayerID, ABuildingBase* InBuilding)
{
	if (!Buildings.Contains(InPlayerID))
	{
		return;
	}
	if (Buildings[InPlayerID].Buildings.Contains(InBuilding))
	{
		Buildings[InPlayerID].Buildings.Remove(InBuilding);
		if (Buildings[InPlayerID].Buildings.Num() <= 0)
		{
			AWW4GameModeBase* WW4GM = UWW4CommonFunctionLibrary::GetWW4GameMode(GetWorld());
			if (WW4GM)
			{
				WW4GM->OnPlayerEliminated(InPlayerID);
			}
		}
	}
}

void UUnitManager::CollectBuildingsAndUnits()
{
	Buildings.Empty();
	for (TActorIterator<ABuildingBase> BuildingItr(GetWorld()); BuildingItr; ++BuildingItr)
	{
		Buildings.Add(BuildingItr->GetOwningPlayerID(), *BuildingItr);
	}
	Units.Empty();
	for (TActorIterator<AUnitBase> UnitItr(GetWorld()); UnitItr; ++UnitItr)
	{
		Units.Add(UnitItr->GetOwningPlayerID(), FUnitsInfo(*UnitItr, UnitItr->GetOwningPlayerID()));
	}
}
