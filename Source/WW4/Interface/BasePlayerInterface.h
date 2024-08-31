// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BasePlayerInterface.generated.h"

UINTERFACE(MinimalAPI)
class UBasePlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WW4_API IBasePlayerInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnBuildingConstructed(int32 ItemID);
};
