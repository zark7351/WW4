// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitFactoryBase.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Component/PlayerBaseComponent.h"
#include "WW4/Core/WW4GameModeBase.h"

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
		AController* Controller = WW4GM->FindPlayerByID(GetOwningPlayerID());
		if (Controller)
		{
			UPlayerBaseComponent* BaseComp = Controller->GetComponentByClass<UPlayerBaseComponent>();
			if (BaseComp)
			{
				BaseComp->SetCurrentFactory(FactoryType, this);
			}
		}
	}
}

void AUnitFactoryBase::BeginPlay()
{
	Super::BeginPlay();
	SetMainFactory();
}
