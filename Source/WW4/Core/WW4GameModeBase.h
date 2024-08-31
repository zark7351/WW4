// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/BaseTypes/BaseTypes.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<int32, AController*>PlayerIDMap;

	UFUNCTION(BlueprintCallable)
	void RegPlayerID(int32 InID, AController* InPlayer);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AController* const FindPlayerByID (int32 InID) const;

	void OnPlayerEliminated(int32 InID);

private:
	class UUnitManager* UnitManager = nullptr;
};
