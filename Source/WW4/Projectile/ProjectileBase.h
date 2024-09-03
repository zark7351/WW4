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

	//void SetProjectileSpeedOverride(float InSpeed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRangeDamage{ false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage{20.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageTypeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinimumDamage{ 5.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageInnerRadius{ 50.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageOuterRadius{ 200.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageFalloff{ 10.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* HitSound;

	UFUNCTION(BlueprintCallable)
	void Explode(AActor* HitActor);

	//不使用ProjectileMovementComponent, 自定义移动
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCustomMovement{ false };

private:

};
