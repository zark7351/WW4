// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WW4/Unit/UnitBase.h"
#include "VehicleBase.generated.h"

/**
 * 
 */
UCLASS()
class WW4_API AVehicleBase : public AUnitBase
{
	GENERATED_BODY()
	
public:

	AVehicleBase();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UVehicleMovementComponent* VehicleMovement;
};
