// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"
#include "WW4/Component/HealthComponent.h"
#include "Components/WidgetComponent.h"

AUnitBase::AUnitBase()
{
	PrimaryActorTick.bCanEverTick = true;
	UnitMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Unit Mesh"));
	UnitMesh->SetCustomDepthStencilValue(1);
	RootComponent = UnitMesh;
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
	HealthBar->SetupAttachment(RootComponent);
	ShowHealthBar(false);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
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
		OnTakeDamage();
		return HealthComponent->OnTakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}
	return 0.0f;
}

void AUnitBase::ShowHealthBar(bool bShow)
{
	if (HealthBar)
	{
		HealthBar->SetVisibility(bShow);
	}
}

void AUnitBase::EnableOutline(bool bEnable)
{
	UnitMesh->MarkRenderStateDirty();
	UnitMesh->bRenderCustomDepth = bEnable;
}

void AUnitBase::OnSelected(bool bSelected)
{
	EnableOutline(bSelected);
	ShowHealthBar(bSelected);
}

void AUnitBase::OnTakeDamage()
{
	ShowHealthBar(true);
}

void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AUnitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
