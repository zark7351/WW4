// Fill out your copyright notice in the Description page of Project Settings.


#include "WW4GameModeBase.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4PlayerController.h"

void AWW4GameModeBase::InitManager()
{
	if (!UnitManager)
	{
		UWorld* World = GetWorld();
		if (World && UnitManagerClass)
		{
			UnitManager = Cast<UUnitManager>(World->GetSubsystemBase(UnitManagerClass));
		}
	}
}

void AWW4GameModeBase::StartPlay()
{
	Super::StartPlay();
	InitManager();
	PlayerIDMap.Empty();
}

void AWW4GameModeBase::SetPlayerID(int32 InID, AWW4PlayerController* InPlayer)
{
	PlayerIDMap.Add(InID, InPlayer);
}

void AWW4GameModeBase::OnPlayerEliminated(int32 InID)
{
	if (PlayerIDMap.Contains(InID))
	{
		PlayerIDMap[InID]->Defeated();
	}
}
