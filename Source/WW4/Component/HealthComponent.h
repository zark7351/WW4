// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthComponent.generated.h"

/**
 * 
 */
UCLASS()
class WW4_API UHealthComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:

	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth{ 100.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Armor{ 20.f };


	UFUNCTION(BlueprintCallable)
	void ShowHealthBar(bool bShow);

	UFUNCTION(BlueprintCallable)
	void UpdateHealth();

	UFUNCTION()
	float OnTakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

private:

	UPROPERTY()
	class UHealthBar* HealthBar{ nullptr };

	float CurrentHealth{ 100.f };

	bool bShowing{ false };
};
