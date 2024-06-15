// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"
#include "Components/BoxComponent.h"
#include "WW4/Component/HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "WW4/AI/Controller/UnitAIControllerBase.h"

AUnitBase::AUnitBase()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
	SetRootComponent(CollisionBox);
	UnitMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Unit Mesh"));
	UnitMesh->SetCustomDepthStencilValue(1);
	UnitMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UnitMesh->SetupAttachment(RootComponent);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetupAttachment(RootComponent);
	HealthComponent->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AUnitAIControllerBase::StaticClass();	
}

void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	UnitController = Cast<AUnitAIControllerBase>(GetController());
	if (UnitController)
	{
		UnitController->ReceiveMoveCompleted.AddDynamic(this, &AUnitBase::OnStopMove);
	}
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

void AUnitBase::StopMoving()
{
	if (UnitController)
	{
		UnitController->StopMovement();
	}
}

void AUnitBase::PauseMoving()
{
	if (UnitController)
	{
		UnitController->PauseMove(UnitController->GetCurrentMoveRequestID());
	}
}

void AUnitBase::ResumeMoving()
{
	if (UnitController)
	{
		UnitController->ResumeMove(UnitController->GetCurrentMoveRequestID());
	}
}

bool AUnitBase::GetIsMoving() const
{
	if (UnitController)
	{
		return UnitController->bMoving;
	}
	return false;
}

void AUnitBase::SetIsMoving(bool InMoving)
{
	if (UnitController)
	{
		UnitController->bMoving = InMoving;
	}
}

void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitBase::OnStopMove(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	SetIsMoving(false);
}


void AUnitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
