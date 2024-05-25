// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	TSubclassOf<class ABuildingGridCell> CellClass;

	void InitCell();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	bool TracePos(FHitResult& OutHitResult);

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UnitID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* BuildingGridInfo;

	UPROPERTY()
	TArray<int32> CellGrid;

	UPROPERTY()
	TArray<ABuildingGridCell*> CellArr;

	UPROPERTY()
	FString CurBuilding;

	bool CanConstruct();

private:

	FVector Offset{ FVector::ZeroVector };

	FVector HitPos{ FVector::ZeroVector };

};
