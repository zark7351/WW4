// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleBase.h"
#include "WW4/Component/VehicleMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

AVehicleBase::AVehicleBase()
{
	VehicleMovement = CreateDefaultSubobject<UVehicleMovementComponent>(TEXT("VehicleMovement"));
	PrimaryActorTick.bCanEverTick = true;
}

void AVehicleBase::SetTurnInPlaceTarget(const FVector& InTargetLocation)
{
	TurningInPlace = true;
	TargetLocation = InTargetLocation;
}

void AVehicleBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TurnInPlace(DeltaSeconds);
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

void AVehicleBase::TurnInPlace(float DeltaSeconds)
{
	if (TurningInPlace)
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
		FRotator CurRotation = GetActorRotation();
		SetActorRotation(FMath::RInterpConstantTo(CurRotation, LookAtRotation, DeltaSeconds, TurnSpeed));
		if (FMath::IsNearlyEqual(CurRotation.Yaw, LookAtRotation.Yaw, 3.0f))
		{
			OnTurnInPlaceFinished.Broadcast(this);
			TurningInPlace = false;
		}
	}
}
