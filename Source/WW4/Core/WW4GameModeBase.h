// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WW4_API AWW4GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUnitManager> UnitManagerClass;

	UFUNCTION(BlueprintCallable)
	void InitManager();

	virtual void StartPlay() override;

private:
	class UUnitManager* UnitManager = nullptr;
};
