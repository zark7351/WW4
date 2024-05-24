// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MinerAIController.generated.h"

/**
 * 
 */
UCLASS()
class WW4_API AMinerAIController : public AAIController
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void Ready();
	
};
