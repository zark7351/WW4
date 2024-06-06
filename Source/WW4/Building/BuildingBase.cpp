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
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
	HealthBar->SetupAttachment(RootComponent);
	static ConstructorHelpers::FClassFinder<UUserWidget>WidgetClass(TEXT("Blueprint'/Game/WW4/Blueprint/UI/WBP_HealthBar.WBP_HealthBar_C'"));
	if (WidgetClass.Succeeded())
	{
		HealthBarWidgetClass = WidgetClass.Class;
	}
	HealthBar->SetWidgetClass(HealthBarWidgetClass);
	ShowHealthBar(false);
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
		OnTakeDamage();
		return HealthComponent->OnTakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}
	return 0.0f;
}

void ABuildingBase::ShowHealthBar(bool bShow)
{
	if (HealthBar)
	{
		HealthBar->SetVisibility(bShow);
	}
}

void ABuildingBase::EnableOutline(bool bEnable)
{
	BuildingMesh->MarkRenderStateDirty();
	BuildingMesh->bRenderCustomDepth = bEnable;
}

void ABuildingBase::OnSelected(bool bSelected)
{
	EnableOutline(bSelected);
	ShowHealthBar(bSelected);
}

void ABuildingBase::OnTakeDamage()
{
	ShowHealthBar(true);
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

