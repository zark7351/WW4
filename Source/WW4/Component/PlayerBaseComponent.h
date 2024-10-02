// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerBaseComponent.generated.h"

//建造、单位控制等基本功能的组件，从WW4PlayerController里解耦出来方便AIController复用

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WW4_API UPlayerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerBaseComponent();


	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ServerSpawnBuilding(int32 InPlayerID, const FItemProductionInfoBase& BuildingInfo, const FVector& Location, const FRotator& Rotation);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSpawnUnit(FItemProductionInfoBase ItemInfo, int32 InPlayerID, const FTransform& Transform, ABuildingBase* OwnerBuilding);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerMoveUnit(AUnitBase* InUnit, FVector Destination);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetTarget(const TArray<AUnitBase*>& Actors, AActor* TargetActor);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnBuildingConstructed(int32 InItemID, bool bConstructOrDestruct);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerDeployUnit(AUnitBase* InUnit);


private:
	class UUnitManager* UnitManager;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
