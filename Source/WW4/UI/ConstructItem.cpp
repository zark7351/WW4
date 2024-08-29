// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructItem.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UConstructItem::NativeConstruct()
{
	if (!Button->OnClicked.IsBound())
	{
		Button->OnClicked.AddDynamic(this, &UConstructItem::OnClicked);
	}
	MaskDynamicMaterialIns = Mask->GetDynamicMaterial();
	EnableMask(false);
	EnableCount(false);
}

void UConstructItem::OnClicked()
{
	switch (ItemState)
	{
	case EConstructItemState::ECS_Normal:
		OnConstrcutItemClickedHandle.Broadcast(ItemInfo, false);
		SetState(EConstructItemState::ECS_Building);
		EnableMask(true);
		if (bUseCount)
		{
			Count = 0;
		}
		break;
	case EConstructItemState::ECS_Building:
		if (bUseCount)
		{
			Count++;
			if (Count > 0)
			{
				EnableCount(true);
			}
		}
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

void UConstructItem::EnableMask1(bool Enable)
{
	if (Mask_1)
	{
		Mask_1->SetVisibility(Enable ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
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
		if (bNeedDeploy)
		{
			SetState(EConstructItemState::ECS_Ready);
			EnableMask1(true);
		}
		else
		{
			OnConstrcutItemClickedHandle.Broadcast(ItemInfo, true);
		}
		if (bUseCount)
		{
			Count--;
			if (Count >= 0)
			{
				OnConstrcutItemClickedHandle.Broadcast(ItemInfo, false);
				if (Count == 0)
				{
					EnableCount(false);
				}
			}
			else
			{
				SetState(EConstructItemState::ECS_Normal);
			}
		}
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

void UConstructItem::EnableCount(bool bEnable)
{
	if (CountText)
	{
		CountText->SetVisibility(bEnable ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
	}
}

void UConstructItem::SetCount(int32 inCount)
{
	if (CountText)
	{
		CountText->SetText(FText::AsNumber(inCount));
	}
}
