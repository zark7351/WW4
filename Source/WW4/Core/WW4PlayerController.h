
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WW4/BaseTypes/BaseTypes.h"
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
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ServerSpawnBuilding(EFaction InFaction, FName BuildingName, const FVector& Location, const FRotator& Rotation);

	UFUNCTION(Server, Reliable)
	void ServerSpawnUnit(EFaction InFaction, TSubclassOf<AUnitBase> UnitType, const FTransform& Transform, ABuildingBase* OwnerBuilding);

	UFUNCTION(Server, Reliable)
	void ServerSpawnVehicle(EFaction InFaction, UClass* VehicleType);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerMoveUnit(AUnitBase* InUnit, FVector Destination);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetTarget(const TArray<AUnitBase*>& Actors, AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetFaction(EFaction InFaction) { Faction = InFaction; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE EFaction GetFaction() { return Faction; }


private:
	class UUnitManager* UnitManager;

	EFaction Faction{ EFaction::EF_Red };
};
