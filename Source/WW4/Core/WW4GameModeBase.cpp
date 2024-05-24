// Fill out your copyright notice in the Description page of Project Settings.


#include "WW4GameModeBase.h"
#include "WW4/Manager/UnitManager.h"

const AUnitManager* AWW4GameModeBase::GetUnitManager()
{
	if (!UnitManager)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			UnitManager = World->SpawnActor<AUnitManager>();
		}
	}
	return UnitManager;
}
