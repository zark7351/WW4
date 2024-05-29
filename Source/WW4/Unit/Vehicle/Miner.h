// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WW4/Unit/Vehicle/VehicleBase.h"
#include "Miner.generated.h"


class AOreRefinery;

/**
 * 
 */
UCLASS()
class WW4_API AMiner : public AVehicleBase
{
	GENERATED_BODY()

public:

	virtual void OnInit() override;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:

	void Rotate(float DeltaSeconds);
};
