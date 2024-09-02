// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingBase.h"
#include "Components/StaticMeshComponent.h"
#include "WW4/Building/BuildingBase.h"
#include "WW4/Component/HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "WW4/Core/WW4PlayerController.h"
#include "WW4/Component/PlayerBaseComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WW4/Interface/BasePlayerInterface.h"

ABuildingBase::ABuildingBase()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	CollisionBox->bDynamicObstacle = true;
	SetRootComponent(CollisionBox);
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BuildingMesh->SetupAttachment(RootComponent);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetupAttachment(RootComponent);
	HealthComponent->SetRelativeLocation(FVector(0.f, 0.f, 250.f));
}

void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();
	InitGrid();
	AController* Controller = UWW4CommonFunctionLibrary::GetPlayerByID(GetWorld(), OwningPlayerID);
	if (Controller)
	{
		UPlayerBaseComponent* BaseComp = Controller->GetComponentByClass<UPlayerBaseComponent>();
		if (BaseComp && BaseComp->WW4PlayerID == Execute_GetOwningPlayerID(this))
		{
			IBasePlayerInterface* Player = Cast<IBasePlayerInterface>(Controller);
			if (Player)
			{
				Player->Execute_OnBuildingConstructed(Controller, ItemInfo.ItemID);
			}
		}
	}
}

void ABuildingBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	auto UnitManager = UWW4CommonFunctionLibrary::GetUnitManager(GetWorld());
	if (UnitManager)
	{
		UnitManager->OnBuildingDestroy(OwningPlayerID,this);
	}
}

void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildingBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABuildingBase, OwningPlayerID);
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
	//EnableOutline(bSelected);
	if (HealthComponent)
	{
		HealthComponent->ShowHealthBar(true);
	}
}

void ABuildingBase::SetFactionStyle_Implementation(EFaction InFaction)
{
	if (FactionMaterialMap.Contains(InFaction))
	{
		BuildingMesh->SetMaterial(0, FactionMaterialMap[InFaction]);
	}
}

void ABuildingBase::SetOwningPlayerID_Implementation(int32 InID)
{
	OwningPlayerID = InID;
}

int32 ABuildingBase::GetOwningPlayerID_Implementation()
{
	return OwningPlayerID;
}

void ABuildingBase::InitGrid()
{
	UDataTable* BuildingGridInfoTable = LoadObject<UDataTable>(nullptr,TEXT("DataTable'/Game/WW4/Datatable/DT_GridInfo.DT_GridInfo'"));
	if (BuildingGridInfoTable)
	{
		FItemProductionInfoBase* Row = BuildingGridInfoTable->FindRow<FItemProductionInfoBase>(FName(*BuildingName),TEXT("Look up for building grid."));
		if (Row)
		{
			BuildingGrid = Row->Grid;
		}
	}
}

