// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "OreRefinery.generated.h"

/**
 * 
 */
UCLASS()
class WW4_API AOreRefinery : public ABuildingBase
{
	GENERATED_BODY()

public:
	AOreRefinery();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* MinerSpawnPoint = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AVehicleBase> MinerClass;

protected:

	virtual void BeginPlay() override;
	
};
