// Fill out your copyright notice in the Description page of Project Settings.


#include "WW4CommonFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/Unit/UnitBase.h"
#include "WW4/Unit/Vehicle/VehicleBase.h"
#include "WW4/Core/WW4PlayerController.h"

UUnitManager*  UWW4CommonFunctionLibrary::GetUnitManager(const UObject* WorldContextObject)
{
	UUnitManager* UnitManager = WorldContextObject->GetWorld()->GetSubsystem<UUnitManager>();
	return UnitManager;
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

void UWW4CommonFunctionLibrary::SpawnUnit(const UObject* WorldContextObject, const EFaction& InFaction, TSubclassOf<AUnitBase> InUnitClass, const FTransform& InTransform, ABuildingBase* InOwnerBuilding)
{
	if (!WorldContextObject)	return;

	AWW4PlayerController* PlayerController = Cast<AWW4PlayerController>(WorldContextObject->GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		PlayerController->ServerSpawnUnit(InFaction, InUnitClass, InTransform, InOwnerBuilding);
	}
}
