// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "BuildingConstructor.generated.h"

UCLASS()
class WW4_API ABuildingConstructor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuildingConstructor();


	UFUNCTION(BlueprintCallable)
	bool Construct();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AConstructGridCell> CellClass;

	void InitCell();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UnitID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* BuildingGridInfo;

	UPROPERTY()
	TArray<int32> CellGrid;

	UPROPERTY(BlueprintReadWrite)
	TArray<AConstructGridCell*> CellArr;

	UPROPERTY()
	FItemProductionInfoBase CurBuildingInfo;

	bool CanConstruct();

	UFUNCTION(BlueprintCallable)
	void ClearCellArr();

private:

	FVector Offset{ FVector::ZeroVector };

	FVector HitPos{ FVector::ZeroVector };

	TArray<class ABuildingBase*> PlayerBuildings;

};
