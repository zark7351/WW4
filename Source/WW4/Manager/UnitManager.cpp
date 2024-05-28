// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitManager.h"
#include "WW4/Building/UnitFactoryBase.h"
#include "WW4/Unit/UnitBase.h"
#include "WW4/Unit/Vehicle/VehicleBase.h"
#include "WW4/Building/BuildingBase.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"

AUnitManager::AUnitManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUnitManager::BeginPlay()
{
	Super::BeginPlay();
}

void AUnitManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitManager::SpawnUnitAtBuilding(EFaction Faction, TSubclassOf<AUnitBase> UnitType, AUnitFactoryBase* SpawnBuilding)
{
	AUnitBase* Unit = nullptr;
	if (SpawnBuilding)
	{
		Unit = GetWorld()->SpawnActor<AUnitBase>(UnitType, SpawnBuilding->GetSpawnTransform());
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

void AUnitManager::SpawnUnit(EFaction Faction, TSubclassOf<AUnitBase> UnitType, const FTransform& Transform, ABuildingBase* OwnerBuilding)
{
	AUnitBase* Unit = GetWorld()->SpawnActor<AUnitBase>(UnitType, Transform);
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

void AUnitManager::SpawnVehicle(EFaction Faction, UClass* VehicleType)
{
	if (CurrentVehicleFactory)
	{
		SpawnUnitAtBuilding(Faction, VehicleType, CurrentVehicleFactory);
	}
}

void AUnitManager::SetCurrentFactory(EContructItemType Type, AUnitFactoryBase* InFactory)
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

void AUnitManager::SpawnBuilding(FName BuildingName, const FVector& Location, const FRotator& Rotation)
{
	if (BuildingGridInfo)
	{
		FBuildingProductionInfo* Row = BuildingGridInfo->FindRow<FBuildingProductionInfo>(BuildingName, "");
		if (Row && Row->ItemClass)
		{
			GetWorld()->SpawnActor<AActor>(Row->ItemClass, Location, Rotation);
		}
	}
}

