// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4CommonFunctionLibrary.generated.h"

/**
 * 
 */

class AUnitBase;
class AUnitFactoryBase;

UCLASS()
class WW4_API UWW4CommonFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Common")
	static AUnitManager* GetUnitManager(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Common")
	static void PrintCommonMessage(const FString& Msg, FColor Color = FColor::Blue);

};
