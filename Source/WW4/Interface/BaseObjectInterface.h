// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "BaseObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UBaseObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WW4_API IBaseObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSelected(bool bSelected);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetTarget(AActor* Targetactor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetFactionStyle(EFaction InFaction);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	EFaction GetFaction() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetOwningPlayerID(int32 InID);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 GetOwningPlayerID();

};
