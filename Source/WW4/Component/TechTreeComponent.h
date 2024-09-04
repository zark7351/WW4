
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "TechTreeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WW4_API UTechTreeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTechTreeComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitConstructItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* BuildingTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* VehicleTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FItemProductionInfoBase> AllItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FItemProductionInfoBase> UnlockedItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> InitUnlockItemsID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSet<int32> BuiltItemsID;

	UFUNCTION(BlueprintCallable)
	void OnNewItemConstructed(int32 InItemID);

	void RefreshHUD();

	UFUNCTION(BlueprintCallable)
	void OnLastItemDestructed(int32 InItemID);

	bool CheckPrerequisite(const FItemProductionInfoBase& CheckItem);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FItemProductionInfoBase FindItemInfobyID(int32 ID) const;
};
