// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleBase.h"
#include "WW4/Component/VehicleMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Components/AudioComponent.h"
#include "TimerManager.h"

AVehicleBase::AVehicleBase()
{
	VehicleMovement = CreateDefaultSubobject<UVehicleMovementComponent>(TEXT("VehicleMovement"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(RootComponent);
	PrimaryActorTick.bCanEverTick = true;
	SetReplicateMovement(false);
}

void AVehicleBase::BeginPlay()
{
	Super::BeginPlay();
	if (MoveSound)
	{
		AudioComponent->SetSound(MoveSound);
	}
}

void AVehicleBase::SetTurnInPlaceTarget(const FVector& InTargetLocation)
{
	TurningInPlace = true;
	TargetLocation = InTargetLocation;
}

void AVehicleBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AVehicleBase, ServerLocation);
	DOREPLIFETIME(AVehicleBase, ServerRotation);
}

void AVehicleBase::OnSetMoving(bool bMoving)
{
	if(AudioComponent)
	{
		if (bMoving)
		{
			if (!AudioComponent->IsPlaying())
			{
				AudioComponent->FadeIn(0.2f);
			}
		}
		else
		{
			//如果改变移动目标，bMoving会变化，这里延迟检查一下是否还在移动，如果停止再StopPlay
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AVehicleBase::DelayStopSound, 0.2f);
		}
	}
}

void AVehicleBase::DelayStopSound()
{
	if (AudioComponent && !GetIsMoving() && !TurningInPlace)
	{
		AudioComponent->FadeOut(0.2f, 0.f);
	}
}

void AVehicleBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (HasAuthority())
	{
		TurnInPlace(DeltaSeconds);
		Rotate(DeltaSeconds);
		ServerLocation = GetActorLocation();
		ServerRotation = GetActorRotation();
	}
	else
	{
		FVector ClientLocation = GetActorLocation();
		FRotator ClientRotation = GetActorRotation();
		SetActorLocation(FMath::VInterpConstantTo(ClientLocation, ServerLocation, DeltaSeconds, VehicleMovement->MaxSpeed));
		SetActorRotation(FMath::RInterpConstantTo(ClientRotation, ServerRotation, DeltaSeconds, TurnSpeed));
	}
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
		SetActorRotation(FMath::RInterpConstantTo(CurRotation, FRotator(CurRotation.Pitch,NewRotation.Yaw,CurRotation.Roll), DeltaSeconds, TurnSpeed));
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
		//GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Green, FString::Printf(TEXT("Vehicle: TurningInPlace %d, LookAtYaw: %f, TempYaw: %f"), TurningInPlace, LookAtRotation.Yaw, TempRot.Yaw));
		if (FMath::IsNearlyEqual(CurRotation.Yaw, LookAtRotation.Yaw))
		{
			OnTurnInPlaceFinished.Broadcast(this);
			TurningInPlace = false;
		}
	}
}
