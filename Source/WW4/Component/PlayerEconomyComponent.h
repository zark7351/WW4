// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "PlayerEconomyComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNoMoneyDelegate, bool, bNoMoney);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBuildingProgressDelegate, FItemProductionInfoBase, Info, float, Progress, bool, bStart);

struct ItemCostInfo
{
	float SpentMoney;
	bool bInProgress;

	ItemCostInfo(float Money = 0.f, bool InProgress = false) :SpentMoney(Money), bInProgress(InProgress) {}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WW4_API UPlayerEconomyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerEconomyComponent();

	virtual void InitializeComponent() override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitMoney{ 10000 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TickTime{ 0.1f };

	UFUNCTION(BlueprintCallable, Blueprintpure)
	FORCEINLINE int32 GetMoney() const { return Money; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void AddCostItem(const FItemProductionInfoBase& Info);

	UFUNCTION()
	void RemoveCostItem(const FItemProductionInfoBase& Info, bool bCancele);

	UFUNCTION()
	void ReturnItemMoney(const FItemProductionInfoBase& Info);


	UPROPERTY(BlueprintAssignable)
	FNoMoneyDelegate NoMoneyDelegate;

	UPROPERTY(BlueprintAssignable)
	FBuildingProgressDelegate BuildingProgressDelegate;
		
private:

	UPROPERTY(Replicated)
	float Money;

	float TargetMoney;

	float TimeSinceLastTick;

	TMap<FItemProductionInfoBase, ItemCostInfo> ItemCostMap;

	TMap<FItemProductionInfoBase, ItemCostInfo> OnHoldItems;

	float TimeElapsed;

	bool bNoMoney{ false };
};
