// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class WW4_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRangeDamage{ false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damange{20.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinimumDamange{ 5.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageInnerRadius{ 50.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageOuterRadius{ 200.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageFalloff{ 10.f };

	UFUNCTION()
	void SetProjectileSpeedOverride(float InSpeed);
};
