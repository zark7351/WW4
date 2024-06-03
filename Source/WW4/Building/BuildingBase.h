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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHealthComponent* HealthComponent;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BuildingName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> BuildingGrid;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BuildingMesh;

	UFUNCTION(BlueprintCallable)
	void InitGrid();

};
