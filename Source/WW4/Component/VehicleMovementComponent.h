// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "VehicleMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = Movement, meta = (BlueprintSpawnableComponent))
class WW4_API UVehicleMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()

public:
	//virtual FVector GetActorFeetLocation() const override;
};
