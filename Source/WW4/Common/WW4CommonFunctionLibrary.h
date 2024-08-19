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

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Common")
	static UUnitManager* GetUnitManager(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Common", meta = (WorldContext = "WorldContextObject"))
	static class AWW4GameModeBase* GetWW4GameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Common", meta = (WorldContext = "WorldContextObject"))
	static class AWW4PlayerController* GetWW4PlayerController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Common")
	static void PrintCommonMessage(const FString& Msg, FColor Color = FColor::Blue);
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Common")
	static void SpawnUnit(const UObject* WorldContextObject, const EFaction& InFaction, TSubclassOf<AUnitBase> InUnitClass, const FTransform& InTransform, class ABuildingBase* InOwnerBuilding);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Common")
	static bool TraceFloorUnderScreenPosition(const UObject* WorldContextObject, FVector2D ScreenPos, FHitResult& OutHitResult);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Common")
	static bool TraceFloorUnderCursor(const UObject* WorldContextObject, FHitResult& OutHitResult);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Common")
	static bool TraceFloorUnderWorldLocation(const UObject* WorldContextObject, FHitResult& OutHitResult, const FVector& InLocation);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Common")
	static bool TraceTargetUnderCursor(const UObject* WorldContextObject, FHitResult& OutHitResult);

	/*
	* 抛体运动，根据落地水平距离，出射角度和高度，计算出射速度。GPT给的算法
	*/
	UFUNCTION(BlueprintCallable, Category = "Math")
	static float SolveInitialVelocity(float x, float theta, float h, float g = 9.8f);

	//计算以目标点为中心的矩形点阵
	UFUNCTION(BlueprintCallable, Category = "Math")
	static TArray<FVector2D> CalcTargetPointsInRec(int32 Num, const FVector2D& TargetPoint, float Spacing);
};
