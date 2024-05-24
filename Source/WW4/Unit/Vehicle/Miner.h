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
	UFUNCTION(BlueprintCallable)
	void SetOwnerOreRefinery(AOreRefinery* InOwnerOreRefinery);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE AOreRefinery* GetOwnerOreRefinery(){ return OwnerOreRefinery; }

public:

	void OnInit();

private:

	AOreRefinery* OwnerOreRefinery = nullptr;
};
