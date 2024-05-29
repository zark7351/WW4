// Fill out your copyright notice in the Description page of Project Settings.


#include "Miner.h"
#include "WW4/AI/Controller/MinerAIController.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/Component/VehicleMovementComponent.h"

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
	Rotate(DeltaSeconds);
}

void AMiner::Rotate(float DeltaSeconds)
{
	if (VehicleMovement && !VehicleMovement->Velocity.IsNearlyZero())
	{
		FRotator NewRotation = VehicleMovement->Velocity.Rotation();
		FRotator CurRotation = GetActorRotation();
		SetActorRotation(FMath::RInterpTo(CurRotation, NewRotation, DeltaSeconds, 5.f));
	}
}
