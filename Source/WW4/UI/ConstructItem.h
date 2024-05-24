// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "ConstructItem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConstrcutItemClicked, const FItemProductionInfoBase&, Info);

UCLASS()
class WW4_API UConstructItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FItemProductionInfoBase ItemInfo;

	UPROPERTY()
	FOnConstrcutItemClicked OnConstrcutItemClickedHandle;

	UFUNCTION()
	void OnClicked();
};
