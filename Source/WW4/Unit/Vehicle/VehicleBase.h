// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WW4/Unit/UnitBase.h"
#include "VehicleBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnInPlaceFinished, AVehicleBase*, Vehicle);

/**
 * 
 */
UCLASS()
class WW4_API AVehicleBase : public AUnitBase
{
	GENERATED_BODY()
	
public:

	AVehicleBase();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnSpeed{500.f};

	UPROPERTY(BlueprintAssignable)
	FOnTurnInPlaceFinished OnTurnInPlaceFinished;

	UFUNCTION(BlueprintCallable)
	void SetTurnInPlaceTarget(const FVector& InTargetLocation);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* MoveSound;

	virtual void OnSetMoving(bool bMoving) override;

	void DelayStopSound();

	bool TurningInPlace{ false };

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UVehicleMovementComponent* VehicleMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* AudioComponent;

	virtual void Tick(float DeltaSeconds) override;

	void Rotate(float DeltaSeconds);
	
	void TurnInPlace(float DeltaSeconds);

	UPROPERTY(Replicated)
	FVector ServerLocation;

	UPROPERTY(Replicated)
	FRotator ServerRotation;

private:

	FVector TargetLocation;
};
