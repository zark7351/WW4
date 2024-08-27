// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "PlayerEconomyComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNoMoneyDelegate, bool, bNoMoney);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBuildingProgressDelegate, FItemProductionInfoBase, Info, float, Progress);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WW4_API UPlayerEconomyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerEconomyComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InitMoney{ 10000 };

	UFUNCTION(BlueprintCallable, Blueprintpure)
	FORCEINLINE int32 GetMoney() const { return Money; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	void AddOrRemoveCostItem(const FItemProductionInfoBase& Info, bool bAdd);

	UPROPERTY(BlueprintAssignable)
	FNoMoneyDelegate NoMoneyDelegate;

	UPROPERTY(BlueprintAssignable)
	FBuildingProgressDelegate BuildingProgressDelegate;
		
private:

	UPROPERTY(Replicated)
	int32 Money;

	TMap<FItemProductionInfoBase, int32> ItemCostMap;

	float TimeElapsed;

	bool bNoMoney{ false };
};
