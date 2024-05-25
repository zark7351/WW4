// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "UnitManager.generated.h"

class AUnitBase;
class AUnitFactoryBase;

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
	FUnitInfoBase(AUnitBase* InUnit, EFaction InFaction = EFaction::EF_RedTeam) { ID = FGuid::NewGuid(); Faction = InFaction; Unit = InUnit; }
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

UCLASS()
class WW4_API AUnitManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AUnitManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* BuildingGridInfo;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SpawnVehicle(EFaction Faction, UClass* VehicleType);

	void SetCurrentFactory(EContructItemType Type, AUnitFactoryBase* InFactory);

	UFUNCTION(Server, Reliable)
	void SpawnUnitAtBuilding(EFaction Faction, TSubclassOf<AUnitBase> UnitType, AUnitFactoryBase* SpawnBuilding);
	UFUNCTION(Server, Reliable)
	void SpawnUnit(EFaction Faction, TSubclassOf<AUnitBase> UnitType, const FTransform& Transform);
	UFUNCTION(Server, Reliable)
	void SpawnBuilding(FName BuildingName,const FVector& Location, const FRotator& Rotation);

private:

	UPROPERTY()
	TMap<EFaction,FUnitsInfo> Units;

	UPROPERTY()
	class AUnitFactoryBase* CurrentVehicleFactory = nullptr;

	UPROPERTY()
	class AUnitFactoryBase* CurrentInfantryFactory = nullptr;


};
