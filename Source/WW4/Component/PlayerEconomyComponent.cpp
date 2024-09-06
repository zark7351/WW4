// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerEconomyComponent.h"
#include "Net/UnrealNetwork.h"

UPlayerEconomyComponent::UPlayerEconomyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	//PrimaryComponentTick.TickInterval = 0.1f;
}

void UPlayerEconomyComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


void UPlayerEconomyComponent::BeginPlay()
{
	Super::BeginPlay();
	Money = InitMoney;
}


void UPlayerEconomyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Money > 0)
	{
		if (bNoMoney)
		{
			bNoMoney = false;
			NoMoneyDelegate.Broadcast(bNoMoney);
		}
		for (auto It = ItemCostMap.CreateIterator(); It; ++It)
		{
			int32 ConstPerTick = It->Key.ItemPrice / (It->Key.ItemProductTime = 0.f ? DeltaTime : It->Key.ItemProductTime) * DeltaTime;
			float Progress = 0.f;
			if (Money > ConstPerTick)
			{
				Money -= ConstPerTick;
				It->Value.SpentMoney += ConstPerTick;
				Progress = It->Value.SpentMoney / It->Key.ItemPrice;
				BuildingProgressDelegate.Broadcast(It->Key, Progress, !It->Value.bInProgress);
				It->Value.bInProgress = It->Value.SpentMoney == 0.f ? false : true;	//这里需要判断下是不是上一步新加进来的，是的话不设成true
				if (It->Value.SpentMoney >= It->Key.ItemPrice)
				{
					It.RemoveCurrent();
				}
			}
			else
			{
				It->Value.SpentMoney += Money;
				Money = 0;
				bNoMoney = true;
				NoMoneyDelegate.Broadcast(bNoMoney);
				break;
			}
		}
	}
}

void UPlayerEconomyComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPlayerEconomyComponent, Money);
}

void UPlayerEconomyComponent::AddCostItem(const FItemProductionInfoBase& Info)
{
	if (OnHoldItems.Contains(Info))
	{
		ItemCostMap.Add(Info, OnHoldItems[Info]);
		OnHoldItems.Remove(Info);
	}
	else
	{
		ItemCostMap.Add(Info, ItemCostInfo());
	}
}

void UPlayerEconomyComponent::RemoveCostItem(const FItemProductionInfoBase& Info, bool bCancele)
{
	if (ItemCostMap.Contains(Info))
	{
		if (bCancele)
		{
			Money += ItemCostMap[Info].SpentMoney;
		}
		else
		{
			OnHoldItems.Add(Info, ItemCostMap[Info]);
		}
		ItemCostMap.Remove(Info);
	}
}

void UPlayerEconomyComponent::ReturnItemMoney(const FItemProductionInfoBase& Info)
{
	Money += Info.ItemPrice;
}
