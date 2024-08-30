// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIPlayerController.generated.h"

/**
 * 
 */

class UPlayerEconomyComponent;
class UPlayerBaseComponent;

UCLASS()
class WW4_API AAIPlayerController : public AAIController
{
	GENERATED_BODY()

public:

	AAIPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerEconomyComponent* EconomyComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerBaseComponent* PlayerBaseComponent;

};
