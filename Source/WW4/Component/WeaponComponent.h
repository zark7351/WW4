// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponComponent.generated.h"

class AProjectileBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WW4_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

	UFUNCTION(BlueprintCallable)
	void BeginFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	virtual void Fire();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Firing{ false };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetFireRange() const { return FireRange; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetFireRange(float InRange) { FireRange = InRange; }

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess="true"))
	float FireDelay = 1.0f;

	float FireRange = 1500.0f;

	UPROPERTY()
	FTimerHandle FireTimer;
};
