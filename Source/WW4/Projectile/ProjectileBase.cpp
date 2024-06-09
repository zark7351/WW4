// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

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
	InitialLifeSpan = 3.0f;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

}

void AProjectileBase::OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::SetProjectileSpeedOverride(float InSpeed)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->InitialSpeed = InSpeed;
		ProjectileMovement->MaxSpeed = InSpeed;
	}
}

