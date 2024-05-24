// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "UnitFactoryBase.generated.h"

/**
 * 
 */
UCLASS()
class WW4_API AUnitFactoryBase : public ABuildingBase
{
	GENERATED_BODY()

public:
	AUnitFactoryBase();

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* SpawnPoint;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AUnitBase> UnitType;

public:
	UFUNCTION()
	const FTransform GetSpawnTransform();

protected:

	void SetMainFactory();

	virtual void BeginPlay() override;
};
