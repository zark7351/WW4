// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleBase.h"
#include "WW4/Component/VehicleMovementComponent.h"

AVehicleBase::AVehicleBase()
{
	VehicleMovement = CreateDefaultSubobject<UVehicleMovementComponent>(TEXT("VehicleMovement"));
	PrimaryActorTick.bCanEverTick = true;
}

void AVehicleBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Rotate(DeltaSeconds);
}

void AVehicleBase::Rotate(float DeltaSeconds)
{
	if (VehicleMovement && GetIsMoving())
	{
		FRotator NewRotation = VehicleMovement->Velocity.Rotation();
		FRotator CurRotation = GetActorRotation();
		SetActorRotation(FMath::RInterpConstantTo(CurRotation, NewRotation, DeltaSeconds, TurnSpeed));
	}
}
