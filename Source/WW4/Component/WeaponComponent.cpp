// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "TimerManager.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Projectile/ProjectileBase.h"
#include "WW4/Unit/UnitBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;	
}

void UWeaponComponent::BeginFire()
{
	GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &UWeaponComponent::Fire, FireDelay, true, 0.f);
	Firing = true;
}

void UWeaponComponent::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimer);
	Firing = false;
}

void UWeaponComponent::Fire_Implementation()
{
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerUnit = Cast<AUnitBase>(GetOwner());
}


void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetOwner()->HasAuthority())
	{
		if (OwnerUnit)
		{
			if (IsTargetInRange() && OwnerUnit->GetIsMoving())
			{
				OwnerUnit->StopMoving();
			}
			TurnToTarget(DeltaTime);
			//UE_LOG(LogTemp, Warning, TEXT("%f"), OwnerUnit->GetActorRotation().Yaw);

			if (IsTargetInRange() && bAimReady)
			{
				if (!Firing)
				{
					BeginFire();
				}
			}
			else if (Firing)
			{
				StopFire();
			}
		}
	}
}

void UWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWeaponComponent, RotateAngle);
}

bool UWeaponComponent::IsTargetInRange() const
{
	if (IsValid(Target))
	{
		FVector Temp = Target->GetActorLocation() - GetOwner()->GetActorLocation();
		Temp.Z = 0.f;
		float Distance = Temp.Length();
		return Distance <= FireRange;
	}
	return false;
}

void UWeaponComponent::TurnToTarget(float DeltaTime)
{
	FRotator CurRot = OwnerUnit->GetActorRotation();
	FRotator TargetRot = CurRot;
	FRotator TempRot = CurRot;
	if (HasTarget())
	{
		FVector LookAtVector = GetTarget()->GetActorLocation() - OwnerUnit->GetActorLocation();
		TargetRot = FRotationMatrix::MakeFromX(LookAtVector).Rotator();
		//UKismetSystemLibrary::DrawDebugArrow(GetWorld(), OwnerUnit->GetActorLocation(), OwnerUnit->GetActorLocation() + TargetRot.Vector() * 200, 2.f, FLinearColor::Red);
	}
	if (OwnerUnit->bHasDestination)
	{
		FVector LookAtVector = OwnerUnit->GetDestination() - OwnerUnit->GetActorLocation();
		TargetRot = FRotationMatrix::MakeFromX(LookAtVector).Rotator();
	}
	TempRot = FMath::RInterpConstantTo(FRotator(CurRot.Pitch,RotateAngle,CurRot.Roll), TargetRot, DeltaTime, TurnSpeed);
	bAimReady = FMath::IsNearlyEqual(RotateAngle,TargetRot.Yaw, 3.0f);
	if (bAimReady)
	{
		return;
	}
	else
	{
		RotateAngle = TempRot.Yaw;
		//GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Red, FString::Printf(TEXT("%f"), TempRot.Yaw));
	}
}
