// Fill out your copyright notice in the Description page of Project Settings.


#include "WW4GameModeBase.h"
#include "WW4/Manager/UnitManager.h"

void AWW4GameModeBase::InitManager()
{
	if (!UnitManager)
	{
		UWorld* World = GetWorld();
		if (World && UnitManagerClass)
		{
			UnitManager = World->SpawnActor<AUnitManager>(UnitManagerClass);
		}
	}
}

void AWW4GameModeBase::StartPlay()
{
	Super::StartPlay();
	InitManager();
}
