// Fill out your copyright notice in the Description page of Project Settings.


#include "WW4CommonFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/Unit/UnitBase.h"
#include "WW4/Unit/Vehicle/VehicleBase.h"
#include "WW4/Core/WW4PlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

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

bool UWW4CommonFunctionLibrary::TraceFloorUnderCursor(const UObject* WorldContextObject, FHitResult& OutHitResult)
{
	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		return false;
	}
	FVector2D ScreenPos = UWidgetLayoutLibrary::GetMousePositionOnViewport(World) * UWidgetLayoutLibrary::GetViewportScale(World);
	FVector WorldPos = FVector::ZeroVector;
	FVector WorldDir = FVector::ZeroVector;
	UGameplayStatics::DeprojectScreenToWorld(World->GetFirstPlayerController(), ScreenPos, WorldPos, WorldDir);
	UKismetSystemLibrary::LineTraceSingleForObjects(World, WorldPos, WorldPos + WorldDir * 100000.f, TArray<TEnumAsByte<EObjectTypeQuery>>({ EObjectTypeQuery::ObjectTypeQuery7 }), false, TArray<AActor*>(), EDrawDebugTrace::Type::None, OutHitResult, true);
	return OutHitResult.bBlockingHit;
}
