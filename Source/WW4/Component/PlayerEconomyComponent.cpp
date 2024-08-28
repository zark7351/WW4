// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerEconomyComponent.h"
#include "Net/UnrealNetwork.h"

UPlayerEconomyComponent::UPlayerEconomyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.2f;
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
			int32 ConstPerTick = It->Key.ItemPrice / (It->Key.ItemProductTime = 0.f ? PrimaryComponentTick.TickInterval : It->Key.ItemProductTime) * PrimaryComponentTick.TickInterval;
			if (Money > ConstPerTick)
			{
				Money -= ConstPerTick;
				It->Value += ConstPerTick;
				float Progress = (float)It->Value / (float)It->Key.ItemPrice;
				BuildingProgressDelegate.Broadcast(It->Key, Progress);
				if (It->Value >= It->Key.ItemPrice)
				{
					It.RemoveCurrent();
				}
			}
			else
			{
				It->Value += Money;
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

