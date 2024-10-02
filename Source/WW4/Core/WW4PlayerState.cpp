// Fill out your copyright notice in the Description page of Project Settings.

#include "WW4PlayerState.h"
#include "Net/UnrealNetwork.h"

void AWW4PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWW4PlayerState, WW4PlayerID);
	DOREPLIFETIME(AWW4PlayerState, Faction);
	DOREPLIFETIME(AWW4PlayerState, Buildings);
	DOREPLIFETIME(AWW4PlayerState, Units);
}

void AWW4PlayerState::SetCurrentFactory(EContructItemType Type, AUnitFactoryBase* InFactory)
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