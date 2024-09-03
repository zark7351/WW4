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


void UPlayerBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UPlayerBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerBaseComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPlayerBaseComponent, WW4PlayerID);
	DOREPLIFETIME(UPlayerBaseComponent, Faction);
	DOREPLIFETIME(UPlayerBaseComponent, Buildings);
	DOREPLIFETIME(UPlayerBaseComponent, Units);
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
}

void UPlayerBaseComponent::ServerSetTarget_Implementation(const TArray<AUnitBase*>& Actors, AActor* TargetActor)
{
	for (AUnitBase* Unit : Actors)
	{
		if (TargetActor != Unit)
		{
			Unit->Execute_SetTarget(Unit, TargetActor);
		}
	}
}


void UPlayerBaseComponent::SetCurrentFactory(EContructItemType Type, AUnitFactoryBase* InFactory)
{
	switch (Type)
	{
	case EContructItemType::ECT_Building:
		break;
	case EContructItemType::ECT_Infantry:
		CurrentInfantryFactory = InFactory;
		break;
	case EContructItemType::ECT_Vehicle:
		CurrentVehicleFactory = InFactory;
		break;
	case EContructItemType::ECT_Max:
		break;
	default:
		break;
	}
}