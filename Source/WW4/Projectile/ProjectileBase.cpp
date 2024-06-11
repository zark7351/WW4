// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Gameframework/DamageType.h"
#include "Kismet/KismetSystemLibrary.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SetRootComponent(CollisionSphere);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionSphere->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InitialLifeSpan =5.0f;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileBase::OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AProjectileBase::Explode()
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
	if (HasAuthority() && bRangeDamage && DamageTypeClass)
	{
		//UKismetSystemLibrary::DrawDebugSphere(this, GetActorLocation(), DamageInnerRadius, 12, FLinearColor::Red, 10.f);
		//UKismetSystemLibrary::DrawDebugSphere(this, GetActorLocation(), DamageOuterRadius, 12,FLinearColor::Blue, 10.f);
		UGameplayStatics::ApplyRadialDamageWithFalloff(this, Damage, MinimumDamage, GetActorLocation(), DamageInnerRadius, DamageOuterRadius, DamageFalloff, DamageTypeClass, TArray<AActor*>({this}));
	}
	Destroy();
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//CheckFireRange();
}

//void AProjectileBase::SetProjectileSpeedOverride(float InSpeed)
//{
//	if (ProjectileMovement)
//	{
//		ProjectileMovement->InitialSpeed = InSpeed;
//		ProjectileMovement->MaxSpeed = InSpeed;
//	}
//}

//void AProjectileBase::CheckFireRange()
//{
//	FVector CurPos = GetActorLocation();
//	FVector MoveVector = CurPos - StartPos;
//	MoveVector.Z = 0.f;
//	if (MoveVector.Length() >= FireRange)
//	{
//		if (bRangeDamage && DamageTypeClass)
//		{
//			UGameplayStatics::ApplyRadialDamageWithFalloff(this, Damage, MinimumDamage, GetActorLocation(), DamageInnerRadius, DamageOuterRadius, DamageFalloff, DamageTypeClass, TArray<AActor*>());
//		}
//		if (HitParticle)
//		{
//			FTransform Transform;
//			Transform.SetLocation(GetActorLocation());
//			Transform.SetRotation(FRotator(FMath::FRandRange(0.f, 360.f), FMath::FRandRange(0.f, 360.f), FMath::FRandRange(0.f, 360.f)).Quaternion());
//			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, Transform);
//		}
//		if (HitSound)
//		{
//			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
//		}
//		Destroy();
//	}
//}

