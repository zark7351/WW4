// Fill out your copyright notice in the Description page of Project Settings.


#include "Miner.h"
#include "WW4/AI/Controller/MinerAIController.h"

void AMiner::OnInit()
{
	AMinerAIController* MinerController = Cast<AMinerAIController>(GetController());
	if (MinerController)
	{
		MinerController->Ready();
	}
	Super::OnInit();
}

void AMiner::BeginPlay()
{
	Super::BeginPlay();
}

void AMiner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
