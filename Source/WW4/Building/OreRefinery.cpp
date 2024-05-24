// Fill out your copyright notice in the Description page of Project Settings.


#include "OreRefinery.h"
#include "WW4/Unit/Vehicle/Miner.h"
#include "Kismet/GameplayStatics.h"

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
		AMiner* Miner = GetWorld()->SpawnActor<AMiner>(MinerClass, Transform);
		if (Miner)
		{
			Miner->SetOwnerOreRefinery(this);
			Miner->OnInit();
		}
	}
}
