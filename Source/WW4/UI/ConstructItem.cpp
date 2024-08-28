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
	UpdateProgress(0.f);
}

void UConstructItem::OnClicked()
{
	switch (ItemState)
	{
	case EConstructItemState::ECS_Normal:
		OnConstrcutItemClickedHandle.Broadcast(ItemInfo, false);
		SetState(EConstructItemState::ECS_Building);
		EnableMask(true);
		break;
	case EConstructItemState::ECS_Building:
		break;
	case EConstructItemState::ECS_Ready:
		OnConstrcutItemClickedHandle.Broadcast(ItemInfo, true);
		SetState(EConstructItemState::ECS_Normal);
		EnableMask(false);
		break;
	case EConstructItemState::ECS_Disabled:
		break;
	case EConstructItemState::ECS_Max:
		break;
	default:
		break;
	}
}

void UConstructItem::EnableMask(bool Enable)
{
	if (Mask)
	{
		Mask->SetVisibility(Enable ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
	}
}

void UConstructItem::UpdateProgress(float Ratio)
{
	if (MaskDynamicMaterialIns)
	{
		MaskDynamicMaterialIns->SetScalarParameterValue(FName("Ratio"), Ratio);
	}
	if (Ratio >= 1.f)
	{
		SetState(EConstructItemState::ECS_Ready);
	}
}

void UConstructItem::SetState(const EConstructItemState& InState)
{
	ItemState = InState;
	if (InState == EConstructItemState::ECS_Disabled)
	{
		Button->SetIsEnabled(false);
	}
	else
	{
		Button->SetIsEnabled(true);
	}
}
