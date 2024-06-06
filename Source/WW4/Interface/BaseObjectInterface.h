// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BaseObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
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

	virtual void OnSelected(bool bSelected);

	virtual void OnTakeDamage();
};