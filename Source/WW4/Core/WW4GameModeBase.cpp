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
	FactionPlayerMap.Empty();
}

void AWW4GameModeBase::SetPlayerFaction(EFaction InFaction, AWW4PlayerController* InPlayer)
{
	FactionPlayerMap.Add(InFaction, InPlayer);
}

void AWW4GameModeBase::OnFactionEliminated(EFaction InFaction)
{
	if (FactionPlayerMap.Contains(InFaction))
	{
		FactionPlayerMap[InFaction]->Defeated();
	}
}
