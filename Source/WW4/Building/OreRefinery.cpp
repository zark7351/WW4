// Fill out your copyright notice in the Description page of Project Settings.


#include "OreRefinery.h"
#include "WW4/Unit/Vehicle/Miner.h"
#include "Kismet/GameplayStatics.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"

AOreRefinery::AOreRefinery()
{
	MinerSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Miner Spawn Point"));
	MinerSpawnPoint->SetupAttachment(RootComponent);
}

void AOreRefinery::BeginPlay()
{
	if (MinerClass)
	{
		FTransform Transform = MinerSpawnPoint->GetComponentTransform();
		UWW4CommonFunctionLibrary::SpawnUnit(GetWorld(), EFaction::EF_Red, MinerClass, Transform, this);
	}
}
