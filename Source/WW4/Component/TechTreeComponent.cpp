#include "TechTreeComponent.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "TechTreeComponent.h"
#include "WW4/Core/WW4PlayerController.h"
#include "WW4/Core/WW4HUD.h"
#include "Net/UnrealNetwork.h"

UTechTreeComponent::UTechTreeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
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

void UTechTreeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UTechTreeComponent, UnlockedItems);
}

void UTechTreeComponent::InitConstructItems()
{
	if (Initialized)
	{
		return;
	}
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
	//服务器端需要单独处理
	if (GetOwner()->HasAuthority())
	{
		OnRep_UnlockedItems();
	}
	Initialized = true;
}

void UTechTreeComponent::OnRep_UnlockedItems()
{
	AWW4PlayerController* Player = Cast<AWW4PlayerController>(GetOwner());
	if (Player)
	{
		AWW4HUD* HUD = Player->GetHUD<AWW4HUD>();
		if (HUD)
		{
			HUD->RefreshConstructItems(UnlockedItems);
		}
	}
}

void UTechTreeComponent::UnlockItems(TArray<int32> InItemsID)
{
	if (!Initialized)
	{
		InitConstructItems();
	}
	if (GetOwner()->HasAuthority())
	{ 
		for (int32 InItemID : InItemsID)
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
			}
		}
		OnRep_UnlockedItems();
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
	}
	//服务器端需要单独处理
	if (GetOwner()->HasAuthority())
	{
		OnRep_UnlockedItems();
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

