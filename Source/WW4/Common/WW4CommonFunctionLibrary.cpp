// Fill out your copyright notice in the Description page of Project Settings.


#include "WW4CommonFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/Unit/UnitBase.h"
#include "WW4/Unit/Vehicle/VehicleBase.h"

AUnitManager* UWW4CommonFunctionLibrary::GetUnitManager(const UObject* WorldContextObject)
{
	AUnitManager* Manager = Cast<AUnitManager>(UGameplayStatics::GetActorOfClass(WorldContextObject, AUnitManager::StaticClass()));
	return Manager;
}

void UWW4CommonFunctionLibrary::PrintCommonMessage(const FString& Msg, FColor Color)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Blue,
			Msg
		);
	}
}
