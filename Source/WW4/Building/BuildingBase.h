// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "BuildingBase.generated.h"


USTRUCT(BlueprintType)
struct WW4_API FBuildingProductionInfo : public FItemProductionInfoBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> Grid;
};


UCLASS()
class WW4_API ABuildingBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuildingBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BuildingName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> BuildingGrid;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BuildingMesh;

	UFUNCTION(BlueprintCallable)
	void InitGrid();

};
