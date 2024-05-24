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


	UFUNCTION(Server, Reliable)
	void Construct();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AStaticMeshActor> CellClass;

	void InitCell();

protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UnitID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* BuildingGridInfo;

	//UPROPERTY()
	//TArray<int32> CellGrid;

	UPROPERTY()
	FString CurBuilding;

private:
	UPROPERTY()
	TArray<class ABuildingGridCell*> CellArr;

	FVector Offset{ FVector::ZeroVector };

};
