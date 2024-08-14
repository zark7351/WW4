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
	EFaction Faction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AUnitBase* Unit;

	FUnitInfoBase() = default;
	FUnitInfoBase(AUnitBase* InUnit, EFaction InFaction = EFaction::EF_Red) { ID = FGuid::NewGuid(); Faction = InFaction; Unit = InUnit; }
};

USTRUCT(BlueprintType)
struct FUnitsInfo
{
	GENERATED_BODY()

	TArray<FUnitInfoBase> Units;

	FUnitsInfo() = default;
	FUnitsInfo(TArray<FUnitInfoBase> InUnits) { Units = InUnits; }
	FUnitsInfo(AUnitBase* InUnit)
	{
		TArray<FUnitInfoBase> UnitsInfo;
		UnitsInfo.Add(FUnitInfoBase(InUnit));
		Units = UnitsInfo;
	}
};

//USTRUCT(BlueprintType)
//struct FBuildingInfoBase
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FGuid ID;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	EFaction Faction;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	ABuildingBase* Building;
//
//	FBuildingInfoBase() = default;
//	FBuildingInfoBase(ABuildingBase* InBuilding, EFaction InFaction = EFaction::EF_Red) { ID = FGuid::NewGuid(); Faction = InFaction; Building = InBuilding; }
//};

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

	void SpawnVehicle(EFaction Faction, UClass* VehicleType);

	void SetCurrentFactory(EContructItemType Type, AUnitFactoryBase* InFactory);

	void SpawnUnit(EFaction Faction, TSubclassOf<AUnitBase> UnitType, AUnitFactoryBase* SpawnBuilding);
	void SpawnUnit(EFaction Faction, TSubclassOf<AUnitBase> UnitType, const FTransform& Transform, class ABuildingBase* OwnerBuilding = nullptr);

	UFUNCTION()
	void SpawnBuilding(EFaction InFaction, FName BuildingName, const FVector& Location, const FRotator& Rotation);

	void OnBuildingDestroy(EFaction InFaction, ABuildingBase* InBuilding);

	UPROPERTY(BlueprintReadWrite)
	TMap<EFaction, FUnitsInfo> Units;
	UPROPERTY(BlueprintReadWrite)
	TMap<EFaction, FBuildingArr> Buildings;

	UPROPERTY()
	class AUnitFactoryBase* CurrentVehicleFactory = nullptr;

	UPROPERTY()
	class AUnitFactoryBase* CurrentInfantryFactory = nullptr;

private:

	void CollectBuildingsAndUnits();
};
