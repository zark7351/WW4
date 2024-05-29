// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleBase.h"
#include "WW4/Component/VehicleMovementComponent.h"

AVehicleBase::AVehicleBase()
{
	VehicleMovement = CreateDefaultSubobject<UVehicleMovementComponent>(TEXT("VehicleMovement"));
	PrimaryActorTick.bCanEverTick = true;
}
