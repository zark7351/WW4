// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseComponent.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Unit/UnitBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Net/UnrealNetwork.h"

UPlayerBaseComponent::UPlayerBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPlayerBaseComponent::ServerDeployUnit_Implementation(AUnitBase* InUnit)
{
	InUnit->HandleDeploy();
}

void UPlayerBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UPlayerBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerBaseComponent::ServerSpawnBuilding_Implementation(int32 InPlayerID, const FItemProductionInfoBase& BuildingInfo, const FVector& Location, const FRotator& Rotation)
{
	UnitManager = UnitManager == nullptr ? UWW4CommonFunctionLibrary::GetUnitManager(GetWorld()) : UnitManager;
	if (UnitManager)
	{
		UnitManager->SpawnBuilding(InPlayerID, BuildingInfo, Location, Rotation);
	}
}

void UPlayerBaseComponent::ServerSpawnUnit_Implementation(FItemProductionInfoBase ItemInfo, int32 InPlayerID, const FTransform& Transform, ABuildingBase* OwnerBuilding)
{
	UnitManager = UnitManager == nullptr ? UWW4CommonFunctionLibrary::GetUnitManager(GetWorld()) : UnitManager;
	if (UnitManager)
	{
		UnitManager->SpawnUnit(ItemInfo, InPlayerID, Transform, OwnerBuilding);
	}
}

void UPlayerBaseComponent::ServerMoveUnit_Implementation(AUnitBase* InUnit, FVector Destination)
{
	UAIBlueprintHelperLibrary::CreateMoveToProxyObject(this, InUnit, Destination);
	InUnit->SetIsMoving(true);
	InUnit->SetDestication(Destination);
}

void UPlayerBaseComponent::ServerSetTarget_Implementation(const TArray<AUnitBase*>& Actors, AActor* TargetActor)
{
	for (AUnitBase* Unit : Actors)
	{
		if (IsValid(Unit) && TargetActor != Unit)
		{
			Unit->Execute_SetTarget(Unit, TargetActor);
		}
	}
}

