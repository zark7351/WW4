// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingBase.h"
#include "Components/StaticMeshComponent.h"
#include "WW4/Building/BuildingBase.h"
#include "WW4/Component/HealthComponent.h"
#include "Components/WidgetComponent.h"


ABuildingBase::ABuildingBase()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	SetRootComponent(BuildingMesh);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetupAttachment(RootComponent);
	HealthComponent->SetRelativeLocation(FVector(0.f, 0.f, 250.f));
}

void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();
	InitGrid();
}

void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABuildingBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (HealthComponent)
	{
		return HealthComponent->OnTakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}
	return 0.0f;
}

void ABuildingBase::EnableOutline(bool bEnable)
{
	BuildingMesh->MarkRenderStateDirty();
	BuildingMesh->bRenderCustomDepth = bEnable;
}

void ABuildingBase::OnSelected_Implementation(bool bSelected)
{
	EnableOutline(bSelected);
	if (HealthComponent)
	{
		HealthComponent->ShowHealthBar(true);
	}
}

void ABuildingBase::InitGrid()
{
	UDataTable* BuildingGridInfoTable = LoadObject<UDataTable>(nullptr,TEXT("DataTable'/Game/WW4/Datatable/DT_GridInfo.DT_GridInfo'"));
	if (BuildingGridInfoTable)
	{
		FBuildingProductionInfo* Row = BuildingGridInfoTable->FindRow<FBuildingProductionInfo>(FName(*BuildingName),TEXT("Look up for building grid."));
		if (Row)
		{
			BuildingGrid = Row->Grid;
		}
	}
}

