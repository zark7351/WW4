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
#include "WW4/Interface/BasePlayerInterface.h"
#include "WW4/Core/WW4PlayerState.h"
#include "WW4/Component/TechTreeComponent.h"


AUnitBase* UUnitManager::SpawnUnit(FItemProductionInfoBase ItemInfo, int32 InPlayerID, AUnitFactoryBase* SpawnBuilding)
{
	AUnitBase* Unit = nullptr;
	if (SpawnBuilding)
	{
		Unit = GetWorld()->SpawnActorDeferred<AUnitBase>(ItemInfo.ItemClass, SpawnBuilding->GetSpawnTransform(), nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		if (Unit)
		{
			Unit->ItemInfo = ItemInfo;
			Unit->SetOwnerBuilding(SpawnBuilding);
			Unit->Execute_SetOwningPlayerID(Unit, InPlayerID);
			AController* Player = UWW4CommonFunctionLibrary::GetWW4PlayerByID(GetWorld(), InPlayerID);
			if (Player)
			{
				AWW4PlayerState* PlayerState = Player->GetPlayerState<AWW4PlayerState>();
				if (PlayerState)
				{
					PlayerState->Units.Add(Unit);
					Unit->Faction = PlayerState->GetFaction();
					Unit->FinishSpawning(SpawnBuilding->GetSpawnTransform());
					Unit->OnInit();
				}
			}
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
	AUnitBase* Unit = GetWorld()->SpawnActorDeferred<AUnitBase>(ItemInfo.ItemClass , Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (Unit)
	{
		Unit->ItemInfo = ItemInfo;
		Unit->SetOwnerBuilding(OwnerBuilding);
		Unit->Execute_SetOwningPlayerID(Unit, InPlayerID);
		AController* Player = UWW4CommonFunctionLibrary::GetWW4PlayerByID(GetWorld(), InPlayerID);
		Unit->SetOwner(Player);
		if (Player)
		{
			AWW4PlayerState* PlayerState = Player->GetPlayerState<AWW4PlayerState>();
			if (PlayerState)
			{
				PlayerState->Units.Add(Unit);
				Unit->Faction = PlayerState->GetFaction();
				Unit->FinishSpawning(Transform);
				Unit->OnInit();
			}
		}
		if (Units.Contains(InPlayerID))
		{
			Units[InPlayerID].Units.Add(FUnitInfoBase(Unit, InPlayerID));
		}
		else
		{
			Units.Add(InPlayerID, FUnitsInfo(Unit, InPlayerID));
		}
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

void UUnitManager::SpawnBuilding(int32 InPlayerID, const FItemProductionInfoBase& BuildingInfo, const FVector& Location, const FRotator& Rotation)
{
	if (BuildingInfo.ItemClass)
	{
		ABuildingBase* Building = GetWorld()->SpawnActorDeferred<ABuildingBase>(BuildingInfo.ItemClass, FTransform(Rotation, Location), nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		if (Building)
		{
			Building->ItemInfo = BuildingInfo;
			Building->Execute_SetOwningPlayerID(Building, InPlayerID);
			AController* Player = UWW4CommonFunctionLibrary::GetWW4PlayerByID(GetWorld(), InPlayerID);
			if (Player)
			{
				AWW4PlayerState* PlayerState = Player->GetPlayerState<AWW4PlayerState>();
				if (PlayerState)
				{
					PlayerState->Buildings.Add(Building);
					Building->Faction = PlayerState->GetFaction();
					Building->FinishSpawning(FTransform(Rotation, Location));
				}
			}
			if (Buildings.Contains(InPlayerID))
			{
				Buildings[InPlayerID].Buildings.Add(Building);
			}
			else
			{
				Buildings.Add(InPlayerID, Building);
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
		if (CheckIsUniqueBuilding(InPlayerID,InBuilding))
		{
			AController* Player = UWW4CommonFunctionLibrary::GetWW4PlayerByID(GetWorld(), InPlayerID);
			UTechTreeComponent* TecComp = Player->GetComponentByClass<UTechTreeComponent>();
			if (TecComp)
			{
				TecComp->OnLastItemDestructed(InBuilding->ItemInfo.ItemID);
			}
		}
		Buildings[InPlayerID].Buildings.Remove(InBuilding);
		AController* Player = UWW4CommonFunctionLibrary::GetWW4PlayerByID(GetWorld(), InPlayerID);
		if (Player)
		{
			AWW4PlayerState* PlayerState = Player->GetPlayerState<AWW4PlayerState>();
			if (PlayerState)
			{
				PlayerState->Buildings.Remove(InBuilding);
			}
		}
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

bool UUnitManager::CheckIsUniqueBuilding(int32 InPlayerID, ABuildingBase* InBuilding)
{
	if (Buildings.Contains(InPlayerID))
	{
		uint8 Count = 0;
		for (auto Building : Buildings[InPlayerID].Buildings)
		{
			if (Building->ItemInfo.ItemID == InBuilding->ItemInfo.ItemID)
			{
				Count += 1;
				if (Count > 1) return false;
			}
		}
	}
	return true;
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
