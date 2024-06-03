// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "TimerManager.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Projectile/ProjectileBase.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;	
}

void UWeaponComponent::BeginFire()
{
	GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &UWeaponComponent::Fire, FireDelay, true);
}

void UWeaponComponent::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimer);
}

void UWeaponComponent::Fire()
{
	if (GetOwner()->HasAuthority())
	{
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, GetComponentLocation(), FRotator());
	}
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	BeginFire();
}


void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
