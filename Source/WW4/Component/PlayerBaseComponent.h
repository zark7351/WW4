// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "PlayerBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WW4_API UPlayerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerBaseComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ServerSpawnBuilding(int32 InPlayerID, FName BuildingName, const FVector& Location, const FRotator& Rotation);

	UFUNCTION(Server, Reliable)
	void ServerSpawnUnit(FItemProductionInfoBase ItemInfo, int32 InPlayerID, const FTransform& Transform, ABuildingBase* OwnerBuilding);

	UFUNCTION(Server, Reliable)
	void ServerSpawnVehicle(FItemProductionInfoBase ItemInfo, int32 InPlayerID);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerMoveUnit(AUnitBase* InUnit, FVector Destination);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetTarget(const TArray<AUnitBase*>& Actors, AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetFactionStyle(EFaction InFaction) { Faction = InFaction; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE EFaction GetFaction() { return Faction; }

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//void Defeated();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnBuildingConstructed(int32 InItemID);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetWW4PlayerID() { return WW4PlayerID; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetWW4PlayerID(int32 InID) { WW4PlayerID = InID; }


private:
	class UUnitManager* UnitManager;

	UPROPERTY(Replicated)
	EFaction Faction{ EFaction::EF_Red };

	UPROPERTY(Replicated)
	int32 WW4PlayerID;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
