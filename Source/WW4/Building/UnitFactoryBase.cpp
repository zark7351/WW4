// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitFactoryBase.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/BaseTypes/BaseTypes.h"

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
	UUnitManager* UnitManager = UWW4CommonFunctionLibrary::GetUnitManager(GetWorld());
	if (UnitManager)
	{
		UnitManager->SetCurrentFactory(EContructItemType::ECT_Building, this);
	}
}

void AUnitFactoryBase::BeginPlay()
{
	Super::BeginPlay();
	SetMainFactory();
}
