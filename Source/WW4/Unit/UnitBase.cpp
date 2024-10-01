// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"
#include "Components/BoxComponent.h"
#include "WW4/Component/HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "WW4/AI/Controller/UnitAIControllerBase.h"
#include "Net/UnrealNetwork.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Core/WW4PlayerController.h"
#include "WW4/Component/PlayerBaseComponent.h"

AUnitBase::AUnitBase()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3); 
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Block);
	SetRootComponent(CollisionBox);
	UnitMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Unit Mesh"));
	//UnitMesh->SetCustomDepthStencilValue(1);
	UnitMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UnitMesh->SetupAttachment(RootComponent);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetupAttachment(RootComponent);
	HealthComponent->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AUnitAIControllerBase::StaticClass();	
	SetFactionStyle_Implementation(Faction);
}

void AUnitBase::SetDestication(const FVector& InDestination)
{
	bHasDestination = true;
	Destination = InDestination;
}

void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	UnitController = Cast<AUnitAIControllerBase>(GetController());
	if (UnitController)
	{
		UnitController->ReceiveMoveCompleted.AddDynamic(this, &AUnitBase::OnStopMove);
	}
	UWorld* World = GetWorld();
	if (World)
	{
		AWW4PlayerController* Player = UWW4CommonFunctionLibrary::GetWW4PlayerController(World);
		if (Player && Player->PlayerBaseComponent && OwningPlayerID == Player->PlayerBaseComponent->WW4PlayerID)
		{
			SetOwner(Player);
		}
	}
}

void AUnitBase::ServerDeploy_Implementation()
{
	if (HasAuthority())
	{
		HandleDeploy();
	}
}

void AUnitBase::HandleDeploy_Implementation()
{

}

void AUnitBase::SetFactionStyle_Implementation(EFaction InFaction)
{
	Faction = InFaction;
	if (FactionMaterialMap.Contains(InFaction))
	{
		UnitMesh->SetMaterial(0, FactionMaterialMap[InFaction]);
	}
}

EFaction AUnitBase::GetFaction_Implementation() const
{
	return Faction;
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
	//EnableOutline(bSelected);
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
	bHasDestination = false;
	Destination = FVector::ZeroVector;
	if (UnitController)
	{
		UnitController->StopMovement();
		UnitController->SetMoving(false);
	}
}

void AUnitBase::PauseMoving()
{
	if (UnitController)
	{
		UnitController->SetMoving(false);
		UnitController->PauseMove(UnitController->GetCurrentMoveRequestID());
	}
}

void AUnitBase::ResumeMoving()
{
	if (UnitController)
	{
		UnitController->SetMoving(true);
		UnitController->ResumeMove(UnitController->GetCurrentMoveRequestID());
	}
}

bool AUnitBase::GetIsMoving() const
{
	if (UnitController)
	{
		return UnitController->GetMoving();
	}
	return false;
}

void AUnitBase::SetIsMoving(bool InMoving)
{
	if (UnitController)
	{
		UnitController->SetMoving(InMoving);
	}
}

void AUnitBase::SetOwningPlayerID_Implementation(int32 InID)
{
	OwningPlayerID = InID;
}

int32 AUnitBase::GetOwningPlayerID_Implementation()
{
	return OwningPlayerID;
}

void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AUnitBase, OwningPlayerID);
}

//const AActor* AUnitBase::GetNetOwner() const
//{
//	return UGameplayStatics::GetPlayerController(this, 0);
//}

void AUnitBase::OnStopMove(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	bHasDestination = false;
	Destination = FVector::ZeroVector;
	SetIsMoving(false);
}


void AUnitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
