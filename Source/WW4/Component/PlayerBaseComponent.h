// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "PlayerBaseComponent.generated.h"

//���졢��λ���ƵȻ������ܵ��������WW4PlayerController������������AIController����

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WW4_API UPlayerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerBaseComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ServerSpawnBuilding(int32 InPlayerID, const FItemProductionInfoBase& BuildingInfo, const FVector& Location, const FRotator& Rotation);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSpawnUnit(FItemProductionInfoBase ItemInfo, int32 InPlayerID, const FTransform& Transform, ABuildingBase* OwnerBuilding);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerMoveUnit(AUnitBase* InUnit, FVector Destination);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetTarget(const TArray<AUnitBase*>& Actors, AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetFaction(EFaction InFaction) { Faction = InFaction; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE EFaction GetFaction() { return Faction; }

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//void Defeated();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnBuildingConstructed(int32 InItemID);

	//UFUNCTION(BlueprintCallable, BlueprintPure)
	//FORCEINLINE int32 GetWW4PlayerID() const { return WW4PlayerID; }
	//UFUNCTION(BlueprintCallable)
	//FORCEINLINE void SetWW4PlayerID(int32 InID) { WW4PlayerID = InID; }

	UPROPERTY(BlueprintReadWrite)
	class AUnitFactoryBase* CurrentVehicleFactory = nullptr;

	UPROPERTY(BlueprintReadWrite)
	class AUnitFactoryBase* CurrentInfantryFactory = nullptr;

	void SetCurrentFactory(EContructItemType Type, AUnitFactoryBase* InFactory);

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int32 WW4PlayerID;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
	TArray<ABuildingBase*>Buildings;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
	TArray<AUnitBase*>Units;

private:
	class UUnitManager* UnitManager;

	UPROPERTY(Replicated)
	EFaction Faction{ EFaction::EF_None };

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};