
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WW4PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WW4_API AWW4PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Server, Reliable)
	void ServerSpawnBuilding(FName BuildingName, const FVector& Location, const FRotator& Rotation);

	UFUNCTION(Server, Reliable)
	void ServerSpawnUnit(EFaction Faction, TSubclassOf<AUnitBase> UnitType, const FTransform& Transform);

private:
	class AUnitManager* UnitManager;
};
