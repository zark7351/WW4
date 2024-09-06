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
	//��֪���Ƿ��б�Ҫ��GPT˵Ҫ
	OnConstrcutItemClicked.Clear();
	OnUnitReady.Clear();
	Super::NativeDestruct();
}

void UConstructItem::OnClicked()
{
	switch (ItemState)
	{
	case EConstructItemState::ECS_Normal:
		if (bMultiBuild)
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
		if (bMultiBuild)
		{
			Count++;
			if (Count > 0)
			{
				ShowCount(true);
			}
		}
		break;
	case EConstructItemState::ECS_OnHold:
		OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::Resume);
		SetState(EConstructItemState::ECS_Building);
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
		if (bMultiBuild)
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
		break;
	case EConstructItemState::ECS_Building:
		SetState(EConstructItemState::ECS_OnHold);
		OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::OnHold);	//��ͣ����
		break;
	case EConstructItemState::ECS_OnHold:
		if (bMultiBuild)
		{
			Count--;
			if (Count == 0) ShowCount(false);
			if (Count < 0)
			{
				SetState(EConstructItemState::ECS_Normal);
				OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::Cancele);	//ȡ������
			}
		}
	case EConstructItemState::ECS_Ready:
		OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::Return);	//�����ʽ�	
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
				OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::RemoveWaitList);	//ȡ���Ŷ�
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

void UConstructItem::EnableWait(bool Enable)
{
	if (Mask_2)
	{
		Mask_2->SetVisibility(Enable ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
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
		if (bMultiBuild)
		{
			Count--;
			if (Count == 0)
			{
				ShowCount(false);
			}
		}
	}
	if (Ratio >= 1.f)
	{
		if (bMultiBuild)
		{
			if (Count == 0)
			{
				SetState(EConstructItemState::ECS_Normal);
				OnUnitReady.Broadcast(ItemInfo, true);	//���һ����ɣ�Menu�Ḻ��ˢ����״̬
			}
			else
			{
				SetState(EConstructItemState::ECS_Building);
				OnUnitReady.Broadcast(ItemInfo, false);	//����Menu����ˢ����״̬
				OnConstrcutItemClicked.Broadcast(ItemInfo, EConstructOperationType::Build);	//����Munu��ˢ����״̬
			}
		}
		else if (bNeedDeploy)
		{
			SetState(EConstructItemState::ECS_Ready);
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
	if (InState == EConstructItemState::ECS_Waiting)
	{
		EnableWait(true);
	}
	else
	{
		EnableWait(false);
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
