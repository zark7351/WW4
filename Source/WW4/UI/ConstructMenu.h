// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WW4/BaseTypes/BaseTypes.h"
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

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UConstructItem> ConstructItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABuildingConstructor> ConstructorcClass;

private:

	UFUNCTION()
	void OnConstructItemClick(const FItemProductionInfoBase& ItemInfo);
};
