// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class WW4_API AUnitAIControllerBase : public AAIController
{
	GENERATED_BODY()
public:
	AUnitAIControllerBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
