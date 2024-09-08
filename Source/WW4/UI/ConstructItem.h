// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "ConstructItem.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EConstructItemState :uint8
{
	ECS_Normal	UMETA(DisplayName = "Normal"),
	ECS_Building	UMETA(DisplayName = "Building"),
	ECS_OnHold	UMETA(DisplayName = "OnHold"),
	ECS_Ready	UMETA(DisplayName = "Ready"),
	ECS_Waiting	UMETA(DisplayName = "Waiting"),
	ECS_Disabled	UMETA(DisplayName = "Disable"),

	ECS_Max	UMETA(DisplayName = "DefaultMax"),
};

UENUM()
enum class EConstructOperationType : uint8
{
	Build,
	Deploy,
	AddWaitList,
	RemoveWaitList,
	Cancele,
	Return,
	OnHold,
	Resume,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConstrcutItemClicked, const FItemProductionInfoBase&, Info, EConstructOperationType, Type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUnitReady, const FItemProductionInfoBase&, Info, bool, bIsLastOne);

UCLASS()
class WW4_API UConstructItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Mask;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Mask_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Mask_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CountText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FItemProductionInfoBase ItemInfo;

	UPROPERTY()
	FOnConstrcutItemClicked OnConstrcutItemClicked;

	UPROPERTY()
	FOnUnitReady OnUnitReady;

	UFUNCTION()
	void OnClicked();

	UFUNCTION(BlueprintCallable)
	void OnRightClicked();

	UFUNCTION(BlueprintCallable)
	void EnableMask(bool Enable);

	UFUNCTION(BlueprintCallable)
	void EnableBlink(bool Enable);

	UFUNCTION(BlueprintCallable)
	void EnableWait(bool Enable);

	UFUNCTION(BlueprintCallable)
	void UpdateProgress(float Ratio, bool bStart);

	UFUNCTION(BlueprintCallable)
	void SetState(const EConstructItemState& InState);

	UFUNCTION(BlueprintCallable)
	void ShowCount(bool bEnable);

	UFUNCTION(BlueprintCallable)
	void SetCount(int32 inCount);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE EConstructItemState GetState() const { return ItemState; }

	UPROPERTY(BlueprintReadWrite)
	int32 Count{ 0 };

	//是否可以累加
	bool bMultiBuild{ false };

	//是否需要部署
	bool bNeedDeploy{ true };

	//是否正在部署
	bool bIsDeploying{ false };

protected:

	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


private:


	float CurRatio;

	UMaterialInstanceDynamic* MaskDynamicMaterialIns;

	EConstructItemState ItemState{ EConstructItemState ::ECS_Normal};
};
