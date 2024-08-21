// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingConstructor.h"
#include "WW4/Other/ConstructGridCell.h"
#include "WW4/Building/BuildingBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WW4/Manager/UnitManager.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "WW4/Core/WW4PlayerController.h"
#include "EngineUtils.h"


ABuildingConstructor::ABuildingConstructor()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool ABuildingConstructor::Construct()
{
	if (CanConstruct())
	{
		AWW4PlayerController* PlayerController = UWW4CommonFunctionLibrary::GetWW4PlayerController(GetWorld());
		if (PlayerController)
		{
			PlayerController->ServerSpawnBuilding(PlayerController->GetWW4PlayerID(), FName(*CurBuilding), HitPos, FRotator::ZeroRotator);
			ClearCellArr();
			return true;
		}
	}
	return false;
}

void ABuildingConstructor::BeginPlay()
{
	Super::BeginPlay();
	PlayerBuildings.Empty();
	for (TActorIterator<ABuildingBase> BuildingItr(GetWorld()); BuildingItr; ++BuildingItr)
	{
		if (BuildingItr->GetOwningPlayerID() == UWW4CommonFunctionLibrary::GetWW4PlayerController(GetWorld())->GetWW4PlayerID())
		{
			PlayerBuildings.Add(*BuildingItr);
		}
	}
}

void ABuildingConstructor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FHitResult HitResult;
	if (UWW4CommonFunctionLibrary::TraceFloorUnderCursor(this, HitResult))
	{
		HitPos = HitResult.ImpactPoint;
		SetActorLocation(HitPos);
	}
	bool OutOfRange = true;
	for (auto Building : PlayerBuildings)
	{
		if (FVector::Dist2D(GetActorLocation(), Building->GetActorLocation()) < Building->BuildDistance)
		{
			OutOfRange = false;
		}
	}
	for (auto Cell: CellArr)
	{
		Cell->bOutOfRange = OutOfRange;
	}
}


void ABuildingConstructor::InitCell()
{
	CellArr.Empty();
	if (BuildingGridInfo)
	{
		TArray<FItemProductionInfoBase*> BuildingInfoRows;
		BuildingGridInfo->GetAllRows("", BuildingInfoRows);
		for (FItemProductionInfoBase* row : BuildingInfoRows)
		{
			if (UnitID == row->ItemID)
			{
				CurBuilding = row->ItemName;
				for (int32 i = 0; i < 25; i++)
				{
					FVector Location;
					Location.X = (i / 5 - 2) * 100;
					Location.Y = (i % 5 - 2) * 100;
					Location += Offset;
					AConstructGridCell* Cell = GetWorld()->SpawnActor<AConstructGridCell>(CellClass, Location, FRotator::ZeroRotator);
					if (Cell)
					{
						//Cell->SetMobility(EComponentMobility::Movable);
						CellArr.Add(Cell);
						bool Contains = row->Grid.Contains(i);
						Cell->bActive = Contains;
						Cell->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
						Cell->SetActorHiddenInGame(!Contains);
					}
				}
				break;
			}
		}
	}
}

bool ABuildingConstructor::CanConstruct()
{
	bool Can = true;
	for (auto Cell:CellArr)
	{
		if (Cell)
		{
			if (Cell->bActive && (Cell->bBlock || Cell->bOutOfRange))
			{
				Can = false;
			}
		}
		else Can = false;
	}
	return Can;
}

void ABuildingConstructor::ClearCellArr()
{
	if (CellArr.Num()>0)
	{
		for (auto Cell : CellArr) 
		{
			Cell->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
			Cell->Destroy();
		}
		CellArr.Empty();
	}
}
