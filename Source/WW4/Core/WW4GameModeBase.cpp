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

void AWW4GameModeBase::RegPlayerID(int32 InID, AController* InPlayer)
{
	PlayerIDMap.Add(InID, InPlayer);
}

AController* const AWW4GameModeBase::FindPlayerByID(int32 InID) const
{
	if (PlayerIDMap.Contains(InID))
	{
		return PlayerIDMap[InID];
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can not find player,ID: %d"), InID);
		return nullptr;
	}
}

void AWW4GameModeBase::OnPlayerEliminated(int32 InID)
{
	if (PlayerIDMap.Contains(InID))
	{
		//PlayerIDMap[InID]->Defeated();
	}
}
