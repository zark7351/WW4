// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4/Interface/BaseObjectInterface.h"
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
class WW4_API ABuildingBase : public AActor, public IBaseObjectInterface
{
	GENERATED_BODY()
	
public:	
	ABuildingBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* HealthBar;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BuildingName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> BuildingGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void ShowHealthBar(bool bShow);

	void EnableOutline(bool bEnable);
	
	UFUNCTION(BlueprintCallable)
	virtual void OnSelected(bool bSelected);

	virtual void OnTakeDamage();

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BuildingMesh;

	UFUNCTION(BlueprintCallable)
	void InitGrid();

};
