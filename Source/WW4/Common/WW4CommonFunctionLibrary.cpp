// Fill out your copyright notice in the Description page of Project Settings.


#include "WW4CommonFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/Unit/UnitBase.h"
#include "WW4/Unit/Vehicle/VehicleBase.h"
#include "WW4/Core/WW4PlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "WW4/Core/WW4GameModeBase.h"
#include "WW4/Component/PlayerBaseComponent.h"

UUnitManager*  UWW4CommonFunctionLibrary::GetUnitManager(const UObject* WorldContextObject)
{
	UUnitManager* UnitManager = WorldContextObject->GetWorld()->GetSubsystem<UUnitManager>();
	return UnitManager;
}

AWW4GameModeBase* UWW4CommonFunctionLibrary::GetWW4GameMode(const UObject* WorldContextObject)
{
	return Cast<AWW4GameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
}

AWW4PlayerController* UWW4CommonFunctionLibrary::GetWW4PlayerController(const UObject* WorldContextObject)
{
	AWW4PlayerController* PlayerController = Cast<AWW4PlayerController>(WorldContextObject->GetWorld()->GetFirstPlayerController());
	return PlayerController;
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

void UWW4CommonFunctionLibrary::SpawnUnit(const UObject* WorldContextObject, FItemProductionInfoBase ItemInfo, const int32& InPlayerID, const FTransform& InTransform, ABuildingBase* InOwnerBuilding)
{
	if (!WorldContextObject)	return;

	AWW4PlayerController* PlayerController = Cast<AWW4PlayerController>(WorldContextObject->GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		PlayerController->PlayerBaseComponent->ServerSpawnUnit(ItemInfo, InPlayerID, InTransform, InOwnerBuilding);
	}
}

bool UWW4CommonFunctionLibrary::TraceFloorUnderScreenPosition(const UObject* WorldContextObject, FVector2D ScreenPos, FHitResult& OutHitResult)
{
	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		return false;
	}
	FVector WorldPos = FVector::ZeroVector;
	FVector WorldDir = FVector::ZeroVector;
	UGameplayStatics::DeprojectScreenToWorld(World->GetFirstPlayerController(), ScreenPos, WorldPos, WorldDir);
	UKismetSystemLibrary::LineTraceSingleForObjects(World, WorldPos, WorldPos + WorldDir * 100000.f, TArray<TEnumAsByte<EObjectTypeQuery>>({ EObjectTypeQuery::ObjectTypeQuery7 }), false, TArray<AActor*>(), EDrawDebugTrace::Type::None, OutHitResult, true);
	return OutHitResult.bBlockingHit;
}

bool UWW4CommonFunctionLibrary::TraceFloorUnderCursor(const UObject* WorldContextObject, FHitResult& OutHitResult)
{
	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		return false;
	}
	FVector2D ScreenPos = UWidgetLayoutLibrary::GetMousePositionOnViewport(World) * UWidgetLayoutLibrary::GetViewportScale(World);
	return TraceFloorUnderScreenPosition(WorldContextObject, ScreenPos, OutHitResult);
}

bool UWW4CommonFunctionLibrary::TraceFloorUnderWorldLocation(const UObject* WorldContextObject, FHitResult& OutHitResult, const FVector& InLocation)
{
	UWorld* World = WorldContextObject->GetWorld();

	return UKismetSystemLibrary::LineTraceSingleForObjects(World, InLocation, InLocation + FVector(0.f, 0.f, -5000.f), TArray<TEnumAsByte<EObjectTypeQuery>>({ EObjectTypeQuery::ObjectTypeQuery7 }), false, TArray<AActor*>(), EDrawDebugTrace::Type::None, OutHitResult, true);
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

	// 将角度转换为弧度
	float radTheta = FMath::DegreesToRadians(theta);
	float A = FMath::Cos(radTheta);
	float B = FMath::Sin(radTheta);

	// 初始猜测值
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

TArray<FVector2D> UWW4CommonFunctionLibrary::CalcTargetPointsInRec(int32 Num, const FVector2D& TargetPoint, float Spacing)
{
	TArray<FVector2D> OutPoints;
	int32 Row = FMath::Floor(FMath::Sqrt((float)Num));
	int32 Col = Row;
	FVector2D MaxPoint = FVector2D(TargetPoint.X + (Col - 1) * Spacing, TargetPoint.Y + (Row - 1) * Spacing);
	FVector2d MidPoint = (TargetPoint + MaxPoint) / 2;
	FVector2D Offset = MidPoint - TargetPoint;
	//先以目标点为第一个点的位置，计算正方形点阵
	for (int32 i = 0; i < Row; i++)
	{
		float OffsetY = i * Spacing;
		for (int32 j = 0; j < Col; j++)
		{
			float OffsetX = j * Spacing;
			OutPoints.Add(FVector2D(TargetPoint.X + OffsetX, TargetPoint.Y + OffsetY));
		}
	}
	int32 Rest = Num - Row * Col;
	//如果有多余的，先在右边加一列
	if (Rest > 0)
	{
		for (int32 i = 0; i < Row; i++)
		{
			float OffsetX = Col * Spacing;
			float OffsetY = i * Spacing;
			OutPoints.Add(FVector2D(TargetPoint.X + OffsetX, TargetPoint.Y + OffsetY));
			Rest--;
			if (Rest <= 0)  break;
		}
	}
	//还有多余的话，再在下面加一行
	if (Rest > 0)
	{
		Col += 1;
		for (int32 i = 0; i < Col; i++)
		{
			float OffsetX = i * Spacing;
			float OffsetY = Row * Spacing;
			OutPoints.Add(FVector2D(TargetPoint.X + OffsetX, TargetPoint.Y + OffsetY));
			Rest--;
			if (Rest <= 0)  break;
		}
	}
	//整体往中心偏移
	for (int32 i = 0; i < OutPoints.Num(); i++)
	{
		OutPoints[i] -= Offset;
	}
	//绕中心旋转45°
	//float RotDegree = 45.f;
	//for (int32 i = 0; i < OutPoints.Num(); i++)
	//{
	//	OutPoints[i].X = (OutPoints[i].X - MidPoint.X) * FMath::Cos(FMath::DegreesToRadians(RotDegree)) - (OutPoints[i].Y - MidPoint.Y) * FMath::Sin(FMath::DegreesToRadians(RotDegree)) + MidPoint.X;
	//	OutPoints[i].Y = (OutPoints[i].X - MidPoint.X) * FMath::Sin(FMath::DegreesToRadians(RotDegree)) + (OutPoints[i].Y - MidPoint.Y) * FMath::Cos(FMath::DegreesToRadians(RotDegree)) + MidPoint.Y;
	//}
	return OutPoints;
}
