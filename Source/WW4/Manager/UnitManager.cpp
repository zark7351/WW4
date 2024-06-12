// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitManager.h"
#include "WW4/Building/UnitFactoryBase.h"
#include "WW4/Unit/UnitBase.h"
#include "WW4/Unit/Vehicle/VehicleBase.h"
#include "WW4/Building/BuildingBase.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UUnitManager::SpawnUnit(EFaction Faction, TSubclassOf<AUnitBase> UnitType, AUnitFactoryBase* SpawnBuilding)
{
	AUnitBase* Unit = nullptr;
	if (SpawnBuilding)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		Unit = GetWorld()->SpawnActor<AUnitBase>(UnitType, SpawnBuilding->GetSpawnTransform(),Params);
		if (Units.Contains(Faction))
		{
			Units[Faction].Units.Add(FUnitInfoBase(Unit));
		}
		else
		{
			Units.Add(Faction, FUnitsInfo(Unit));
		}
	}
}

void UUnitManager::SpawnUnit(EFaction Faction, TSubclassOf<AUnitBase> UnitType, const FTransform& Transform, ABuildingBase* OwnerBuilding)
{
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AUnitBase* Unit = GetWorld()->SpawnActor<AUnitBase>(UnitType, Transform, Params);
	if (Unit)
	{
		Unit->SetOwnerBuilding(OwnerBuilding);
		if (Units.Contains(Faction))
		{
			Units[Faction].Units.Add(FUnitInfoBase(Unit));
		}
		else
		{
			Units.Add(Faction, FUnitsInfo(Unit));
		}
		Unit->OnInit();
	}
}

bool UUnitManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return UKismetSystemLibrary::IsServer(Outer);
}

void UUnitManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUnitManager::Deinitialize()
{
	Super::Deinitialize();
}

void UUnitManager::SpawnVehicle(EFaction Faction, UClass* VehicleType)
{
	if (CurrentVehicleFactory)
	{
		SpawnUnit(Faction, VehicleType, CurrentVehicleFactory);
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

void UUnitManager::SpawnBuilding(FName BuildingName, const FVector& Location, const FRotator& Rotation)
{
	if (BuildingGridInfo)
	{
		FBuildingProductionInfo* Row = BuildingGridInfo->FindRow<FBuildingProductionInfo>(BuildingName, "");
		if (Row && Row->ItemClass)
		{
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			GetWorld()->SpawnActor<AActor>(Row->ItemClass, Location, Rotation, Params);
		}
	}
}

