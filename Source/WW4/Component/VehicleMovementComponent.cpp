// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleMovementComponent.h"

FVector UVehicleMovementComponent::GetActorFeetLocation() const
{
	return UpdatedComponent ? UpdatedComponent->GetComponentLocation() : FNavigationSystem::InvalidLocation;
}
