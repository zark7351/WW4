// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WW4GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WW4_API AWW4GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void InitManager();

	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AUnitManager> UnitManagerClass;

private:
	class AUnitManager* UnitManager = nullptr;
};
