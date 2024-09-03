// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WW4/Interface/BasePlayerInterface.h"
#include "AIPlayerController.generated.h"

/**
 * 
 */

class UPlayerEconomyComponent;
class UPlayerBaseComponent;
class UTechTreeComponent;

UCLASS()
class WW4_API AAIPlayerController : public AAIController, public IBasePlayerInterface
{
	GENERATED_BODY()

public:

	AAIPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerEconomyComponent* EconomyComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerBaseComponent* PlayerBaseComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTechTreeComponent* TechTreeComponent;

	virtual void SetPlayerFaction_Implementation(const EFaction& InFaction) override;
	virtual EFaction GetPlayerFaction_Implementation() const override;
};
