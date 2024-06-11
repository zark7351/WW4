// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "TimerManager.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Projectile/ProjectileBase.h"

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
}


void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

