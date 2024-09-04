#include "TechTreeComponent.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "TechTreeComponent.h"
#include "WW4/Core/WW4PlayerController.h"
#include "WW4/Core/WW4HUD.h"

UTechTreeComponent::UTechTreeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UTechTreeComponent::BeginPlay()
{
	Super::BeginPlay();
	InitConstructItems();
}


void UTechTreeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTechTreeComponent::InitConstructItems()
{
	AllItems.Empty();
	UnlockedItems.Empty();
	if (BuildingTable)
	{
		TArray<FName>RowNames = BuildingTable->GetRowNames();
		for (const FName& RowName : RowNames)
		{
			FItemProductionInfoBase* Row = BuildingTable->FindRow< FItemProductionInfoBase>(RowName, TEXT(""));
			if (Row)
			{
				AllItems.Add(*Row);
				if (InitUnlockItemsID.Contains(Row->ItemID))
				{
					UnlockedItems.Add(*Row);
				}
			}
		}
	}
	if (VehicleTable)
	{
		TArray<FName>RowNames = VehicleTable->GetRowNames();
		for (const FName& RowName : RowNames)
		{
			FItemProductionInfoBase* Row = VehicleTable->FindRow< FItemProductionInfoBase>(RowName, TEXT(""));
			if (Row)
			{
				AllItems.Add(*Row);
				if (InitUnlockItemsID.Contains(Row->ItemID))
				{
					UnlockedItems.Add(*Row);
				}
			}
		}
	}
}

void UTechTreeComponent::OnNewItemConstructed(int32 InItemID)
{
	if (!BuiltItemsID.Contains(InItemID))
	{
		BuiltItemsID.Add(InItemID);
		for (FItemProductionInfoBase Info : AllItems)
		{
			if (Info.ItemID != InItemID)
			{
				if (!UnlockedItems.Contains(Info))
				{
					if (CheckPrerequisite(Info))
					{
						UnlockedItems.Add(Info);
					}
				}
			}
		}
		RefreshHUD();
	}
}


void UTechTreeComponent::OnLastItemDestructed(int32 InItemID)
{
	if (BuiltItemsID.Contains(InItemID))
	{
		BuiltItemsID.Remove(InItemID);
		for (int32 i = UnlockedItems.Num() - 1; i >= 0; --i)
		{
			if (UnlockedItems[i].PrerequisiteItemsID.Contains(InItemID))
			{
				UnlockedItems.RemoveAt(i);
			}
		}
		RefreshHUD();
	}
}

void UTechTreeComponent::RefreshHUD()
{
	AWW4PlayerController* Player = Cast<AWW4PlayerController>(GetOwner());
	if (Player)
	{
		AWW4HUD* HUD = Cast<AWW4HUD>(Player->GetHUD());
		if (HUD)
		{
			HUD->RefreshConstructItems(UnlockedItems);
		}
	}
}

bool UTechTreeComponent::CheckPrerequisite(const FItemProductionInfoBase& CheckItem)
{
	for (int32 ID : CheckItem.PrerequisiteItemsID)
	{
		if (!BuiltItemsID.Contains(ID))
		{
			return false;
		}
	}
	return true;
}

FItemProductionInfoBase UTechTreeComponent::FindItemInfobyID(int32 ID) const
{
	for (auto Item : AllItems)
	{
		if (Item.ItemID == ID)
		{
			return Item;
		}
	}
	return FItemProductionInfoBase();
}

