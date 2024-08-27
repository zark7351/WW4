// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerEconomyComponent.h"
#include "Net/UnrealNetwork.h"

UPlayerEconomyComponent::UPlayerEconomyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.2f;
}


void UPlayerEconomyComponent::BeginPlay()
{
	Super::BeginPlay();
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
		for (TPair<FItemProductionInfoBase, int32> Pair : ItemCostMap)
		{
			int32 ConstPerTick = Pair.Key.ItemPrice / (Pair.Key.ItemProductTime = 0.f ? PrimaryComponentTick.TickInterval : Pair.Key.ItemProductTime) * PrimaryComponentTick.TickInterval;
			if (Money > ConstPerTick)
			{
				Money -= ConstPerTick;
				Pair.Value += ConstPerTick;
				BuildingProgressDelegate.Broadcast(Pair.Key, Pair.Value / Pair.Key.ItemPrice);
				if (Pair.Value >= Pair.Key.ItemPrice)
				{
					ItemCostMap.Remove(Pair.Key);
				}
			}
			else
			{
				Pair.Value += Money;
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

void UPlayerEconomyComponent::AddOrRemoveCostItem(const FItemProductionInfoBase& Info, bool bAdd)
{
	if (bAdd)
	{
		ItemCostMap.Add(Info, 0);
	}
	else
	{
		ItemCostMap.Remove(Info);
	}
}

