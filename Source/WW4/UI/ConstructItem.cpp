// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructItem.h"
#include "Components/Button.h"

void UConstructItem::NativeConstruct()
{
	Button->OnClicked.AddDynamic(this, &UConstructItem::OnClicked);
}

void UConstructItem::OnClicked()
{
	OnConstrcutItemClickedHandle.Broadcast(ItemInfo);
}
