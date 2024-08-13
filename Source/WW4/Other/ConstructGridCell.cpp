// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructGridCell.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetSystemLibrary.h"


AConstructGridCell::AConstructGridCell()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AConstructGridCell::BeginPlay()
{
	Super::BeginPlay();
	SetStyle(false);
}

void AConstructGridCell::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CurStyle != TraceBlock())
	{
		SetStyle(bBlock);
		CurStyle = bBlock;
	}
}

void AConstructGridCell::SetStyle(bool bBlocked)
{
	SetDecalMaterial(bBlocked ? RedMaterial : GreenMaterial);
}

bool AConstructGridCell::TraceBlock()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	FHitResult HitResult;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery8);
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);
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
	bBlock = HitResult.bBlockingHit;
	return bBlock;
}
