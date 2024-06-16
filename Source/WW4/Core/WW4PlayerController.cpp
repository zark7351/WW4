

#include "WW4PlayerController.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Unit/UnitBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void AWW4PlayerController::ServerSpawnBuilding_Implementation(FName BuildingName, const FVector& Location, const FRotator& Rotation)
{
	UnitManager = UnitManager == nullptr ? UWW4CommonFunctionLibrary::GetUnitManager(GetWorld()) : UnitManager;
	if (UnitManager)
	{
		UnitManager->SpawnBuilding(BuildingName, Location, Rotation);
	}
}

void AWW4PlayerController::ServerSpawnVehicle_Implementation(EFaction Faction, UClass* VehicleType)
{
	UnitManager = UnitManager == nullptr ? UWW4CommonFunctionLibrary::GetUnitManager(GetWorld()) : UnitManager;
	if (UnitManager)
	{
		UnitManager->SpawnVehicle(Faction, VehicleType);
	}
}

void AWW4PlayerController::ServerSpawnUnit_Implementation(EFaction Faction, TSubclassOf<AUnitBase> UnitType, const FTransform& Transform, ABuildingBase* OwnerBuilding)
{
	UnitManager = UnitManager == nullptr ? UWW4CommonFunctionLibrary::GetUnitManager(GetWorld()) : UnitManager;
	if (UnitManager)
	{
		UnitManager->SpawnUnit(Faction, UnitType, Transform,OwnerBuilding);
	}
}

void AWW4PlayerController::ServerMoveUnits_Implementation(const TArray<AUnitBase*>& InUnits, FVector Destination)
{
	
	for (AUnitBase* Unit:InUnits)
	{
		UAIBlueprintHelperLibrary::CreateMoveToProxyObject(this, Unit, Destination);
		Unit->SetIsMoving(true);
	}
}
