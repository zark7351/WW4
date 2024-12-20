// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponComponent.generated.h"

class AProjectileBase;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WW4_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

	UFUNCTION(BlueprintCallable)
	void BeginFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Fire();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRange{ 1500.0f };

	//�����Ƿ�����ת
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanRotate{ false };

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
	float RotateAngle;

	bool bAimReady{ false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnSpeed{ 500.f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AUnitBase* OwnerUnit{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Firing{ false };

	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* InTarget);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE AActor* GetTarget() const { return Target; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool HasTarget() const { return IsValid(Target); }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsTargetInRange() const;

	UFUNCTION(BlueprintCallable)
	void TurnToTarget(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* FireSound;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess="true"))
	float FireDelay = 1.0f;

	UPROPERTY()
	FTimerHandle FireTimer;

	UPROPERTY()
	AActor* Target{ nullptr };
};
