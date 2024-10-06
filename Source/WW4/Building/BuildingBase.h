// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4/Interface/BaseObjectInterface.h"
#include "BuildingBase.generated.h"


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

	UPROPERTY(EditAnywhere)
	USoundBase* ConstructSound;

	UPROPERTY(EditAnywhere)
	USoundBase* DestructSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BuildingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BuildingName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> BuildingGrid;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	EFaction Faction;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void EnableOutline(bool bEnable);

	virtual void OnSelected_Implementation(bool bSelected);

	virtual void SetFactionStyle_Implementation(EFaction InFaction) override;
	virtual EFaction GetFaction_Implementation() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EFaction, UMaterialInterface*> FactionMaterialMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuildDistance{ 1000 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemProductionInfoBase ItemInfo;

	virtual void SetOwningPlayerID_Implementation(int32 InID) override;

	virtual int32 GetOwningPlayerID_Implementation() override;


	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int32 OwningPlayerID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* DestructEffect;

private:


	UFUNCTION(BlueprintCallable)
	void InitGrid();

};
