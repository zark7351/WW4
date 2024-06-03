// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

float UHealthComponent::OnTakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = DamageAmount * (1 - Armor / 100.f);
	CurrentHealth = FMath::Clamp(CurrentHealth-FinalDamage, 0.f, MaxHealth);
	if (CurrentHealth <= 0.f)
	{
		GetOwner()->Destroy();
	}
	return FinalDamage;
}

