// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPlayerController.h"
#include "WW4/Component/PlayerEconomyComponent.h"
#include "WW4/Component/PlayerBaseComponent.h"

AAIPlayerController::AAIPlayerController()
{
	EconomyComponent = CreateDefaultSubobject<UPlayerEconomyComponent>(TEXT("EconomyComponent"));
	PlayerBaseComponent = CreateDefaultSubobject<UPlayerBaseComponent>(TEXT("PlayerBaseComponent"));
}

void AAIPlayerController::SetPlayerFaction_Implementation(const EFaction& InFaction)
{
	PlayerBaseComponent->SetFaction(InFaction);
}

EFaction AAIPlayerController::GetPlayerFaction_Implementation() const
{
	return PlayerBaseComponent->GetFaction();
}