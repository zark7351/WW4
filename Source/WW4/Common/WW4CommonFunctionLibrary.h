// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4/Manager/UnitManager.h"
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
	static UUnitManager* GetUnitManager(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Common")
	static void PrintCommonMessage(const FString& Msg, FColor Color = FColor::Blue);
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Common")
	static void SpawnUnit(const UObject* WorldContextObject, const EFaction& InFaction, TSubclassOf<AUnitBase> InUnitClass, const FTransform& InTransform, class ABuildingBase* InOwnerBuilding);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Common")
	static bool TraceFloorUnderCursor(const UObject* WorldContextObject, FHitResult& OutHitResult);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Common")
	static bool TraceTargetUnderCursor(const UObject* WorldContextObject, FHitResult& OutHitResult);

	/*
	* 抛体运动，根据落地水平距离，出射角度和高度，计算出射速度。GPT给的算法！牛逼，一次验证通过！
	*/
	UFUNCTION(BlueprintCallable, Category = "Math")
	static float SolveInitialVelocity(float x, float theta, float h, float g = 9.8f);
};
