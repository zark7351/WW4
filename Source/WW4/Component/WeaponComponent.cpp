// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "TimerManager.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Projectile/ProjectileBase.h"
#include "WW4/Unit/UnitBase.h"

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
	if (HasTarget() && IsTargetInRange())
	{
		if (OwnerUnit)
		{
			if (OwnerUnit->GetIsMoving())
			{
				OwnerUnit->StopMoving();
			}
			if (TurnToTarget(DeltaTime))
			{
				if (!Firing)
				{
					BeginFire();
				}
			}
		}
	}
	else if (Firing)
	{
		StopFire();
	}
}

bool UWeaponComponent::IsTargetInRange() const
{
	if (Target)
	{
		FVector Temp = Target->GetActorLocation() - GetOwner()->GetActorLocation();
		Temp.Z = 0.f;
		float Distance = Temp.Length();
		return Distance <= FireRange;
	}
	return false;
}

bool UWeaponComponent::TurnToTarget(float DeltaTime)
{
	if (!OwnerUnit)
	{
		return false;
	}
	if (OwnerUnit->GetIsMoving())
	{
		return false;
	}
	else
	{
		FVector LookAtVector = GetTarget()->GetActorLocation() - OwnerUnit->GetActorLocation();
		FRotator LookAtRotation = FRotationMatrix::MakeFromX(LookAtVector).Rotator();
		if (!bSelfRotate)
		{
			FRotator CurRot = OwnerUnit->GetActorRotation();
			FRotator TempRot = FMath::RInterpConstantTo(CurRot, LookAtRotation, DeltaTime, TurnSpeed);
			OwnerUnit->SetActorRotation(FRotator(CurRot.Pitch, TempRot.Yaw, CurRot.Roll));
			if (FMath::IsNearlyEqual(CurRot.Yaw, LookAtRotation.Yaw, 3.0f))
			{
				return true;
			}
		}
		else
		{
			//TODO: ×Ô×ªÎäÆ÷
		}
	}
	return false;
}

