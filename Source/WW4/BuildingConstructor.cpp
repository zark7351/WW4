// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingConstructor.h"
#include "WW4/Other/BuildingGridCell.h"
#include "WW4/Building/BuildingBase.h"

ABuildingConstructor::ABuildingConstructor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void ABuildingConstructor::Construct_Implementation()
{

}

void ABuildingConstructor::BeginPlay()
{
	Super::BeginPlay();
	InitCell();	
}

void ABuildingConstructor::InitCell()
{
	//CellArr.Empty();
	if (BuildingGridInfo)
	{
		TArray<FBuildingProductionInfo*> BuildingInfoRows;
		BuildingGridInfo->GetAllRows("", BuildingInfoRows);
		for (FBuildingProductionInfo* row : BuildingInfoRows)
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
					ABuildingGridCell* Cell = GetWorld()->SpawnActor<ABuildingGridCell>(Location, FRotator());
					if (Cell)
					{
						bool Contains = row->Grid.Contains(i);
						Cell->bEnabled = Contains;
						Cell->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
						Cell->SetActorHiddenInGame(!Contains);
					}
				}
				break;
			}
		}

	}
}


void ABuildingConstructor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

