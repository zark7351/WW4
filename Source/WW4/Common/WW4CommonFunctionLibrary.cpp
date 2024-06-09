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

bool UWW4CommonFunctionLibrary::TraceTargetUnderCursor(const UObject* WorldContextObject, FHitResult& OutHitResult)
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
	UKismetSystemLibrary::LineTraceSingleForObjects(World, WorldPos, WorldPos + WorldDir * 100000.f, TArray<TEnumAsByte<EObjectTypeQuery>>({ EObjectTypeQuery::ObjectTypeQuery8, EObjectTypeQuery::ObjectTypeQuery9}), false, TArray<AActor*>(), EDrawDebugTrace::Type::None, OutHitResult, true);
	return OutHitResult.bBlockingHit;
}

float UWW4CommonFunctionLibrary::SolveInitialVelocity(float x, float theta, float h, float g)
{
	x /= 100.0f;
	h /= 100.0f;

	// ���Ƕ�ת��Ϊ����
	float radTheta = FMath::DegreesToRadians(theta);
	float A = FMath::Cos(radTheta);
	float B = FMath::Sin(radTheta);

	// ��ʼ�²�ֵ
	float v0 = 10.0f;
	float tolerance = 0.001f;
	int maxIterations = 1000;
	int iterations = 0;

	while (iterations < maxIterations)
	{
		float f = x * g - v0 * A * (v0 * B + FMath::Sqrt(FMath::Square(v0 * B) + 2 * g * h));
		float f_prime = -A * (2 * v0 * B + FMath::Sqrt(FMath::Square(v0 * B) + 2 * g * h) +
			(v0 * B * B) / FMath::Sqrt(FMath::Square(v0 * B) + 2 * g * h));

		float new_v0 = v0 - f / f_prime;

		if (FMath::Abs(new_v0 - v0) < tolerance)
		{
			v0 = new_v0;
			break;
		}

		v0 = new_v0;
		iterations++;
	}

	if (iterations >= maxIterations)
	{
		UE_LOG(LogTemp, Warning, TEXT("Maximum iterations reached without convergence."));
	}
	return v0 * 100.0f;
}
