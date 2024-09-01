// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4/Interface/BaseObjectInterface.h"
#include "BuildingBase.generated.h"


//USTRUCT(BlueprintType)
//struct WW4_API FItemProductionInfoBase : public FItemProductionInfoBase
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<int32> Grid;
//};

UCLASS()
class WW4_API ABuildingBase : public AActor, public IBaseObjectInterface
{
	GENERATED_BODY()
	
public:	
	ABuildingBase();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHealthComponent* HealthComponent;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BuildingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BuildingName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> BuildingGrid;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void EnableOutline(bool bEnable);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSelected(bool bSelected);
	virtual void OnSelected_Implementation(bool bSelected);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetFactionStyle(EFaction InFaction);
	virtual void SetFactionStyle_Implementation(EFaction InFaction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EFaction, UMaterialInterface*> FactionMaterialMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuildDistance{ 1000 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemProductionInfoBase ItemInfo;

	virtual void SetOwningPlayerID_Implementation(int32 InID) override;

	virtual int32 GetOwningPlayerID_Implementation() override;

private:


	UFUNCTION(BlueprintCallable)
	void InitGrid();

	UPROPERTY(Replicated)
	int32 OwningPlayerID;

};
