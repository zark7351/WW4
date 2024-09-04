// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Gameframework/DamageType.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WW4/Interface/BaseObjectInterface.h"

AProjectileBase::AProjectileBase()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SetRootComponent(CollisionSphere);
	CollisionSphere->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel4);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECR_Ignore);
	CollisionSphere->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InitialLifeSpan =5.0f;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	if (bCustomMovement)
	{
		ProjectileMovement->Deactivate();
	}
}

void AProjectileBase::OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == TargetActor)
	{
		Explode(OtherActor);
	}
	else
	{
		IBaseObjectInterface* HitObject = Cast<IBaseObjectInterface>(OtherActor);
		IBaseObjectInterface* OwnerObject = GetOwner() ? Cast<IBaseObjectInterface>(GetOwner()) : nullptr;
		if (HitObject && OwnerObject && HitObject->Execute_GetFaction(OtherActor) == OwnerObject->Execute_GetFaction(GetOwner()))
		{
			return;
		}
		else
		{
			Explode(OtherActor);
		}
	}
}

void AProjectileBase::Explode(AActor* HitActor)
{
	if (HitParticle)
	{
		FTransform Transform;
		Transform.SetLocation(GetActorLocation());
		Transform.SetRotation(FRotator(FMath::FRandRange(0.f, 360.f), FMath::FRandRange(0.f, 360.f), FMath::FRandRange(0.f, 360.f)).Quaternion());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, Transform);
	}
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
	if (HasAuthority() && DamageTypeClass)
	{
		if (bRangeDamage)
		{
			UGameplayStatics::ApplyRadialDamageWithFalloff(this, Damage, MinimumDamage, GetActorLocation(), DamageInnerRadius, DamageOuterRadius, DamageFalloff, DamageTypeClass, TArray<AActor*>({ this }));
		}
		else
		{
			UGameplayStatics::ApplyDamage(HitActor, Damage, nullptr, nullptr, DamageTypeClass);
		}
	}
	Destroy();
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}