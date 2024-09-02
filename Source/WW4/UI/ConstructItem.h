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
	ECS_Ready	UMETA(DisplayName = "Ready"),
	ECS_Disabled	UMETA(DisplayName = "Disable"),

	ECS_Max	UMETA(DisplayName = "DefaultMax"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConstrcutItemClicked, const FItemProductionInfoBase&, Info, bool, bReady);

UCLASS()
class WW4_API UConstructItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Mask;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Mask_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CountText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FItemProductionInfoBase ItemInfo;

	UPROPERTY()
	FOnConstrcutItemClicked OnConstrcutItemClickedHandle;

	UFUNCTION()
	void OnClicked();

	UFUNCTION(BlueprintCallable)
	void EnableMask(bool Enable);

	UFUNCTION(BlueprintCallable)
	void EnableMask1(bool Enable);

	UFUNCTION(BlueprintCallable)
	void UpdateProgress(float Ratio);

	UFUNCTION(BlueprintCallable)
	void SetState(const EConstructItemState& InState);

	UFUNCTION(BlueprintCallable)
	void EnableCount(bool bEnable);

	UFUNCTION(BlueprintCallable)
	void SetCount(int32 inCount);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE EConstructItemState GetState() const { return ItemState; }

	bool bNeedDeploy{ true };

	bool bUseCount{ false };

	bool bIsDeploying{ false };

	UPROPERTY(BlueprintReadWrite)
	int32 Count{ -1 };

private:

	UMaterialInstanceDynamic* MaskDynamicMaterialIns;

	EConstructItemState ItemState{ EConstructItemState ::ECS_Normal};
};
