// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4PlayerState.generated.h"

/**
 * 
 */

class ABuildingBase;
class AUnitBase;

UCLASS()
class WW4_API AWW4PlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadWrite)
	class AUnitFactoryBase* CurrentVehicleFactory = nullptr;

	UPROPERTY(BlueprintReadWrite)
	class AUnitFactoryBase* CurrentInfantryFactory = nullptr;

	void SetCurrentFactory(EContructItemType Type, AUnitFactoryBase* InFactory);

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int32 WW4PlayerID;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
	TArray<ABuildingBase*>Buildings;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
	TArray<AUnitBase*>Units;

	UPROPERTY(Replicated, EditAnywhere)
	EFaction Faction{ EFaction::ET_Blue };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetFaction(EFaction InFaction) { Faction = InFaction; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE EFaction GetFaction() { return Faction; }
};
