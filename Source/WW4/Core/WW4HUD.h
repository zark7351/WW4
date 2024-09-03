// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4HUD.generated.h"

/**
 * 
 */
UCLASS()
class WW4_API AWW4HUD : public AHUD
{
	GENERATED_BODY()


public:
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RefreshItemGroupState(const FItemProductionInfoBase& Info, bool bEnable);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RefreshConstructItems(const TArray<FItemProductionInfoBase>& Items);
};
