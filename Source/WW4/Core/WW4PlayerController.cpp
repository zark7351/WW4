

#include "WW4PlayerController.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Unit/UnitBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Net/UnrealNetwork.h"
#include "WW4/Component/PlayerEconomyComponent.h"


AWW4PlayerController::AWW4PlayerController()
{
	EconomyComponent = CreateDefaultSubobject<UPlayerEconomyComponent>(TEXT("EconomyComponent"));
}

void AWW4PlayerController::ServerSpawnBuilding_Implementation(int32 InPlayerID, FName BuildingName, const FVector& Location, const FRotator& Rotation)
{
	UnitManager = UnitManager == nullptr ? UWW4CommonFunctionLibrary::GetUnitManager(GetWorld()) : UnitManager;
	if (UnitManager)
	{
		UnitManager->SpawnBuilding(InPlayerID, BuildingName, Location, Rotation);
	}
}

void AWW4PlayerController::ServerSpawnVehicle_Implementation(FItemProductionInfoBase ItemInfo, int32 InPlayerID)
{
	UnitManager = UnitManager == nullptr ? UWW4CommonFunctionLibrary::GetUnitManager(GetWorld()) : UnitManager;
	if (UnitManager)
	{
		UnitManager->SpawnVehicle(ItemInfo, InPlayerID);
	}
}

void AWW4PlayerController::ServerSpawnUnit_Implementation(FItemProductionInfoBase ItemInfo, int32 InPlayerID, const FTransform& Transform, ABuildingBase* OwnerBuilding)
{
	UnitManager = UnitManager == nullptr ? UWW4CommonFunctionLibrary::GetUnitManager(GetWorld()) : UnitManager;
	if (UnitManager)
	{
		UnitManager->SpawnUnit(ItemInfo, InPlayerID, Transform, OwnerBuilding);
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
		if (TargetActor != Unit)
		{
			Unit->Execute_SetTarget(Unit, TargetActor);
		}
	}
}

void AWW4PlayerController::Defeated_Implementation()
{

}

void AWW4PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWW4PlayerController, WW4PlayerID);
	DOREPLIFETIME(AWW4PlayerController, Faction);
}
