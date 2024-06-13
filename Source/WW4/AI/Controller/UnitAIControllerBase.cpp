// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitAIControllerBase.h"
#include "Navigation/CrowdFollowingComponent.h"

AUnitAIControllerBase::AUnitAIControllerBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
}
