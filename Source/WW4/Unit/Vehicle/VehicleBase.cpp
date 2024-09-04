// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleBase.h"
#include "WW4/Component/VehicleMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

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
	//Rotate(DeltaSeconds);
}

void AVehicleBase::Rotate(float DeltaSeconds)
{
	if (VehicleMovement && GetIsMoving() && !TurningInPlace)
	{
		FRotator CurRotation = GetActorRotation();
		//这里要判断一下，不然速度接近0时会抽搐
		FRotator NewRotation = VehicleMovement->Velocity.IsNearlyZero()?CurRotation:VehicleMovement->Velocity.Rotation();
		//UKismetSystemLibrary::DrawDebugArrow(GetWorld(),
		//	GetActorLocation(),
		//	GetActorLocation() + NewRotation.Vector() * 500,
		//	5.f,
		//	FLinearColor::Yellow,
		//	1000.f
		//);
		SetActorRotation(FMath::RInterpConstantTo(CurRotation, NewRotation, DeltaSeconds, TurnSpeed));
	}
}

void AVehicleBase::TurnInPlace(float DeltaSeconds)
{
	if (TurningInPlace)
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
		FRotator CurRotation = GetActorRotation();
		FRotator TempRot = FMath::RInterpConstantTo(CurRotation, FRotator(CurRotation.Pitch, LookAtRotation.Yaw, CurRotation.Roll), DeltaSeconds, TurnSpeed);
		SetActorRotation(TempRot);
		if (FMath::IsNearlyEqual(CurRotation.Yaw, LookAtRotation.Yaw))
		{
			OnTurnInPlaceFinished.Broadcast(this);
			TurningInPlace = false;
		}
	}
}
