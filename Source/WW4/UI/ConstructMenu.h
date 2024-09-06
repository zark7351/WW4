// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4/UI/ConstructItem.h"
#include "ConstructMenu.generated.h"

/**
 * 
 */
UCLASS()
class WW4_API UConstructMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UConstructMenu(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* UGP_Building;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* UGP_Vehicle;
	
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void InitAllConstructionList(const TArray<FItemProductionInfoBase>& Items);

	//刷新同组其他Item的状态，其本身状态由自己控制
	UFUNCTION(BlueprintCallable)
	void RefreshGroupState(const FItemProductionInfoBase& ItemInfo, bool bEnable);

	UFUNCTION(BlueprintCallable)
	void UpdateItemProgress(const FItemProductionInfoBase& Info, float Ratio, bool bStart);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UConstructItem> ConstructItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABuildingConstructor> ConstructorcClass;

private:

	UFUNCTION()
	void OnConstructItemClick(const FItemProductionInfoBase& ItemInfo, EConstructOperationType Type);

	UFUNCTION()
	void OnUnitReady(const FItemProductionInfoBase& ItemInfo, bool bIsLastOne);

	TMap<FItemProductionInfoBase, UConstructItem*> ItemInfoMap;
	TArray<FItemProductionInfoBase> WaitingItems;
};
