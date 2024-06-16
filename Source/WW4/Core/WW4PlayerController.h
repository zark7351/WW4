
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WW4PlayerController.generated.h"

/**
 * 
 */

class AUnitBase;

UCLASS()
class WW4_API AWW4PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Server, Reliable)
	void ServerSpawnBuilding(FName BuildingName, const FVector& Location, const FRotator& Rotation);

	UFUNCTION(Server, Reliable)
	void ServerSpawnUnit(EFaction Faction, TSubclassOf<AUnitBase> UnitType, const FTransform& Transform, ABuildingBase* OwnerBuilding);

	UFUNCTION(Server, Reliable)
	void ServerSpawnVehicle(EFaction Faction, UClass* VehicleType);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerMoveUnits(const TArray<AUnitBase*>& InUnits, FVector Destination);

private:
	class UUnitManager* UnitManager;
};
