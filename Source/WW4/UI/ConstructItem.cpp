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
	SetState(EConstructItemState::ECS_Normal);
	ShowCount(false);
}

void UConstructItem::NativeDestruct()
{
	//不知道是否有必要？GPT说要
	OnConstrcutItemClicked.Clear();
	OnUnitReady.Clear();
	Super::NativeDestruct();
}

void UConstructItem::OnClicked()
{
	switch (ItemState)
	{
	case EConstructItemState::ECS_Normal:
		if (bUseCount)
		{
			Count++;
			if (Count == 1)
			{
				OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::Build);
				SetState(EConstructItemState::ECS_Building);
			}
			if (Count > 1)
			{
				ShowCount(true);
			}
		}
		else
		{
			OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::Build);
			SetState(EConstructItemState::ECS_Building);
		}
		break;
	case EConstructItemState::ECS_Building:
		if (bOnHold)
		{
			OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::Resume);
			SetState(EConstructItemState::ECS_Building);
			bOnHold = false;
		}
		if (bUseCount)
		{
			Count++;
			if (Count > 0)
			{
				ShowCount(true);
			}
		}
		break;
	case EConstructItemState::ECS_Ready:
		if (!bIsDeploying)
		{
			OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::Deploy);
			//SetState(EConstructItemState::ECS_Normal);
			bIsDeploying = true;
		}
		break;
	case EConstructItemState::ECS_Waiting:
		if (bUseCount)
		{
			Count++;
			if (Count == 1)
			{
				ShowCount(true);
				OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::AddWaitList);
			}
		}
		break;
	case EConstructItemState::ECS_Disabled:
		break;
	case EConstructItemState::ECS_Max:
		break;
	default:
		break;
	}
}

void UConstructItem::OnRightClicked()
{
	switch (ItemState)
	{
	case EConstructItemState::ECS_Normal:
		if (bUseCount && Count > 0)
		{
			Count--;
			if (Count == 0)
			{
				ShowCount(false);
				OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::RemoveWaitList);	//暂停建造
			}
		}
		break;
	case EConstructItemState::ECS_Building:
		if (!bOnHold)
		{
			bOnHold = true;
			SetState(EConstructItemState::ECS_OnHold);
			OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::OnHold);	//暂停建造
		}
		break;
	case EConstructItemState::ECS_OnHold:
		if (bUseCount)
		{
			Count--;
			if (Count == 0) ShowCount(false);
			if (Count < 0)
			{
				bOnHold = false;
				SetState(EConstructItemState::ECS_Normal);
				OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::Cancele);	//取消建造
			}
		}
	case EConstructItemState::ECS_Ready:
		OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::Return);	//返还资金	
		SetState(EConstructItemState::ECS_Normal);
		break;
	case EConstructItemState::ECS_Waiting:
		if (bInWaitList)
		{
			Count--;
			if (Count <= 0)
			{
				bInWaitList = false;
				ShowCount(false);
				OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::RemoveWaitList);	//取消排队
			}
		}
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

void UConstructItem::EnableBlink(bool Enable)
{
	if (Mask_1)
	{
		Mask_1->SetVisibility(Enable ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
	}
}

void UConstructItem::UpdateProgress(float Ratio, bool bStart)
{
	CurRatio = Ratio;
	if (MaskDynamicMaterialIns)
	{
		MaskDynamicMaterialIns->SetScalarParameterValue(FName("Ratio"), Ratio);
	}
	if (bStart)
	{
		Count--;
		if (Count == 0)
		{
			ShowCount(false);
		}
	}
	if (Ratio >= 1.f)
	{
		OnUnitReady.Broadcast(ItemInfo);
		if (bNeedDeploy)
		{
			SetState(EConstructItemState::ECS_Ready);
		}
		if (bUseCount)
		{
			if (Count >= 0)
			{
				OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::Build);
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
	if (InState == EConstructItemState::ECS_Ready)
	{
		EnableBlink(true);
	}
	else
	{
		EnableBlink(false);
	}
	if (InState == EConstructItemState::ECS_Building || (InState == EConstructItemState::ECS_OnHold))
	{
		EnableMask(true);
	}
	else
	{
		EnableMask(false);
	}
}

void UConstructItem::ShowCount(bool bEnable)
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
