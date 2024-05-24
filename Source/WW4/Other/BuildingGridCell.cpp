// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingGridCell.h"
#include "Components/MeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void ABuildingGridCell::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CurStyle != TraceBlock())
	{
		SetStyle(bBlock);
		CurStyle = bBlock;
	}
}

void ABuildingGridCell::SetStyle(bool bBlocked)
{
	GetStaticMeshComponent()->SetScalarParameterValueOnMaterials(FName(TEXT("Enable")), bBlocked ? 0.f : 1.f);
}

bool ABuildingGridCell::TraceBlock()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	FHitResult HitResult;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery7);
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery8);
	UKismetSystemLibrary::BoxTraceSingleForObjects(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + FVector(0.f, 0.f, 200.f),
		FVector(45.f, 45.f, 5.f),
		FRotator(),
		ObjectTypes,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::Type::None,
		HitResult,
		true
	);
	if (HitResult.bBlockingHit)
	{
		bBlock = true;
		return true;
	}
	return false;
}
