// Fill out your copyright notice in the Description page of Project Settings.


#include "Miner.h"
#include "WW4/AI/Controller/MinerAIController.h"

void AMiner::SetOwnerOreRefinery(AOreRefinery* InOwnerOreRefinery)
{
	OwnerOreRefinery = InOwnerOreRefinery;
}

void AMiner::OnInit()
{
	AMinerAIController* MinerController = Cast<AMinerAIController>(GetController());
	if (MinerController)
	{
		MinerController->Ready();
	}
}
