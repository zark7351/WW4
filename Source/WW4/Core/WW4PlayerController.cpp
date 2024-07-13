

#include "WW4PlayerController.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Unit/UnitBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void AWW4PlayerController::ServerSpawnBuilding_Implementation(EFaction InFaction, FName BuildingName, const FVector& Location, const FRotator& Rotation)
{
	UnitManager = UnitManager == nullptr ? UWW4CommonFunctionLibrary::GetUnitManager(GetWorld()) : UnitManager;
	if (UnitManager)
	{
		UnitManager->SpawnBuilding(InFaction, BuildingName, Location, Rotation);
	}
}

void AWW4PlayerController::ServerSpawnVehicle_Implementation(EFaction InFaction, UClass* VehicleType)
{
	UnitManager = UnitManager == nullptr ? UWW4CommonFunctionLibrary::GetUnitManager(GetWorld()) : UnitManager;
	if (UnitManager)
	{
		UnitManager->SpawnVehicle(InFaction, VehicleType);
	}
}

void AWW4PlayerController::ServerSpawnUnit_Implementation(EFaction InFaction, TSubclassOf<AUnitBase> UnitType, const FTransform& Transform, ABuildingBase* OwnerBuilding)
{
	UnitManager = UnitManager == nullptr ? UWW4CommonFunctionLibrary::GetUnitManager(GetWorld()) : UnitManager;
	if (UnitManager)
	{
		UnitManager->SpawnUnit(InFaction, UnitType, Transform,OwnerBuilding);
	}
}

void AWW4PlayerController::ServerMoveUnit_Implementation(AUnitBase* InUnit, FVector Destination)
{
	UAIBlueprintHelperLibrary::CreateMoveToProxyObject(this, InUnit, Destination);
	InUnit->SetIsMoving(true);
}

void AWW4PlayerController::ServerSetTarget_Implementation(const TArray<AUnitBase*>& Actors, AActor* TargetActor)
{
	for (AUnitBase* Unit : Actors)
	{
		Unit->Execute_SetTarget(Unit, TargetActor);
	}
}
