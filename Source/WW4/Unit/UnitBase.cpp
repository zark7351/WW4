// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"
#include "WW4/Component/HealthComponent.h"

AUnitBase::AUnitBase()
{
	PrimaryActorTick.bCanEverTick = true;
	UnitMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Unit Mesh"));
	RootComponent = UnitMesh;
}

void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUnitBase::OnInit()
{
}

float AUnitBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (HealthComponent)
	{
		return HealthComponent->OnTakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}
	return 0.0f;
}

void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AUnitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
