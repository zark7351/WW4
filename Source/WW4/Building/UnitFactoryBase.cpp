// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitFactoryBase.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Core/WW4GameModeBase.h"
#include "WW4/Core/WW4PlayerState.h"

AUnitFactoryBase::AUnitFactoryBase()
{
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(RootComponent);
}

const FTransform AUnitFactoryBase::GetSpawnTransform()
{
	if (SpawnPoint)
	{
		return SpawnPoint->GetComponentTransform();
	}
	return FTransform();
}

void AUnitFactoryBase::SetMainFactory()
{
	AWW4GameModeBase* WW4GM = UWW4CommonFunctionLibrary::GetWW4GameMode(GetWorld());
	if (WW4GM)
	{
		AController* Controller = WW4GM->FindPlayerByID(OwningPlayerID);
		if (Controller)
		{
			AWW4PlayerState* PlayerState = Controller->GetPlayerState<AWW4PlayerState>();
			if (PlayerState)
			{
				PlayerState->SetCurrentFactory(FactoryType, this);
			}
		}
	}
}

void AUnitFactoryBase::BeginPlay()
{
	Super::BeginPlay();
	SetMainFactory();
}
