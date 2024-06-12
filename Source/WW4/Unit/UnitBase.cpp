// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"
#include "WW4/Component/HealthComponent.h"
#include "Components/WidgetComponent.h"

AUnitBase::AUnitBase()
{
	PrimaryActorTick.bCanEverTick = true;
	UnitMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Unit Mesh"));
	UnitMesh->SetCustomDepthStencilValue(1);
	UnitMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UnitMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
	SetRootComponent(UnitMesh);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetupAttachment(RootComponent);
	HealthComponent->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
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
		return HealthComponent->OnTakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}
	return 0.0f;
}

void AUnitBase::EnableOutline(bool bEnable)
{
	UnitMesh->MarkRenderStateDirty();
	UnitMesh->bRenderCustomDepth = bEnable;
}

void AUnitBase::OnSelected_Implementation(bool bSelected)
{
	EnableOutline(bSelected);
	if (HealthComponent)
	{
		HealthComponent->ShowHealthBar(bSelected);
	}
}

void AUnitBase::SetTarget_Implementation(AActor* Targetactor)
{

}

void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AUnitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
