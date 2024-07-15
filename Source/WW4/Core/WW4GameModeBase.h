// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4GameModeBase.generated.h"

class AWW4PlayerController;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<EFaction, AWW4PlayerController*>FactionPlayerMap;

	UFUNCTION(BlueprintCallable)
	void SetPlayerFaction(EFaction InFaction, AWW4PlayerController* InPlayer);

	void OnFactionEliminated(EFaction InFaction);

private:
	class UUnitManager* UnitManager = nullptr;
};
