// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructItem.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UConstructItem::NativeConstruct()
{
	if (!Button->OnClicked.IsBound())
	{
		Button->OnClicked.AddDynamic(this, &UConstructItem::OnClicked);
	}
	MaskDynamicMaterialIns = Mask->GetDynamicMaterial();
	EnableMask(false);
}

void UConstructItem::OnClicked()
{
	OnConstrcutItemClickedHandle.Broadcast(ItemInfo);
}

void UConstructItem::EnableMask(bool Enable)
{
	if (Mask)
	{
		Mask->SetVisibility(Enable ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
	}
}

void UConstructItem::UpdateMask(float Ratio)
{
	if (MaskDynamicMaterialIns)
	{
		MaskDynamicMaterialIns->SetScalarParameterValue(FName("Ratio"), Ratio);
	}
}
