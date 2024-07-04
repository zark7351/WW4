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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnSpeed{500.f};

	UPROPERTY(BlueprintAssignable)
	FOnTurnInPlaceFinished OnTurnInPlaceFinished;

	UFUNCTION(BlueprintCallable)
	void SetTurnInPlaceTarget(const FVector& InTargetLocation);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UVehicleMovementComponent* VehicleMovement;

	virtual void Tick(float DeltaSeconds) override;

	void Rotate(float DeltaSeconds);
	
	void TurnInPlace(float DeltaSeconds);

private:

	bool TurningInPlace{ false };

	FVector TargetLocation;
};
