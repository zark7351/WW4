// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "UnitManager.generated.h"


class AUnitBase;
class AUnitFactoryBase;
class ABuildingBase;

USTRUCT(BlueprintType)
struct FUnitInfoBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AUnitBase* Unit;

	FUnitInfoBase() = default;
	FUnitInfoBase(AUnitBase* InUnit, int32 InPlayerID) { ID = FGuid::NewGuid(); PlayerID = InPlayerID; Unit = InUnit; }
};

USTRUCT(BlueprintType)
struct FUnitsInfo
{
	GENERATED_BODY()

	TArray<FUnitInfoBase> Units;

	FUnitsInfo() = default;
	FUnitsInfo(TArray<FUnitInfoBase> InUnits) { Units = InUnits; }
	FUnitsInfo(AUnitBase* InUnit, int32 InPlayerID)
	{
		TArray<FUnitInfoBase> UnitsInfo;
		UnitsInfo.Add(FUnitInfoBase(InUnit, InPlayerID));
		Units = UnitsInfo;
	}
};

USTRUCT(BlueprintType)
struct FBuildingArr
{
	GENERATED_BODY()

	TArray<ABuildingBase*> Buildings;

	FBuildingArr() = default;
	FBuildingArr(const TArray<ABuildingBase*>& InBuildings) { Buildings = InBuildings; }
	FBuildingArr(ABuildingBase* InBuilding)
	{
		Buildings.Add(InBuilding);
	}
};

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class WW4_API UUnitManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* BuildingGridInfo;

	void SpawnVehicle(FItemProductionInfoBase ItemInfo, int32 InPlayerID);

	void SetCurrentFactory(EContructItemType Type, AUnitFactoryBase* InFactory);

	AUnitBase* SpawnUnit(FItemProductionInfoBase ItemInfo, int32 InPlayerID, AUnitFactoryBase* SpawnBuilding);
	AUnitBase* SpawnUnit(FItemProductionInfoBase ItemInfo, int32 InPlayerID, const FTransform& Transform, class ABuildingBase* OwnerBuilding = nullptr);

	UFUNCTION()
	void SpawnBuilding(int32 InPlayerID, FName BuildingName, const FVector& Location, const FRotator& Rotation);

	void OnBuildingDestroy(int32 InPlayerID, ABuildingBase* InBuilding);

	UPROPERTY(BlueprintReadWrite)
	TMap<int32, FUnitsInfo> Units;
	UPROPERTY(BlueprintReadWrite)
	TMap<int32, FBuildingArr> Buildings;

	UPROPERTY()
	class AUnitFactoryBase* CurrentVehicleFactory = nullptr;

	UPROPERTY()
	class AUnitFactoryBase* CurrentInfantryFactory = nullptr;

private:

	void CollectBuildingsAndUnits();
};
