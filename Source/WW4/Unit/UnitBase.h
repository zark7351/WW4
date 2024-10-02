#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4/Building/BuildingBase.h"
#include "WW4/Interface/BaseObjectInterface.h"
#include "AIController.h"
#include "UnitBase.generated.h"

class AWW4PlayerController;

UCLASS()
class WW4_API AUnitBase : public APawn, public IBaseObjectInterface
{
	GENERATED_BODY()

public:
	AUnitBase();
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetOwnerBuilding(ABuildingBase* InBuilding) { OwnerBuilding = InBuilding; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE ABuildingBase* GetOwnerBuilding() { return OwnerBuilding; }


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFaction Faction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EFaction, UMaterialInterface*> FactionMaterialMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemProductionInfoBase ItemInfo;

	virtual void SetFactionStyle_Implementation(EFaction InFaction) override;

	virtual EFaction GetFaction_Implementation() const override;

	UFUNCTION(BlueprintNativeEvent)
	void HandleDeploy();

	virtual void OnInit();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void EnableOutline(bool bEnable);

	virtual void OnSelected_Implementation(bool bSelected) override;

	virtual void SetTarget_Implementation(AActor* Targetactor) override;

	UFUNCTION(BlueprintCallable)
	void StopMoving();

	UFUNCTION(BlueprintCallable)
	void PauseMoving();

	UFUNCTION(BlueprintCallable)
	void ResumeMoving();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsMoving() const;

	UFUNCTION(BlueprintCallable)
	void SetIsMoving(bool InMoving);

	virtual void SetOwningPlayerID_Implementation(int32 InID) override;

	virtual int32 GetOwningPlayerID_Implementation() override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int32 OwningPlayerID;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE FVector GetDestination() const { return Destination; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void SetDestication(const FVector& InDestination);

	UPROPERTY(BlueprintReadOnly)
	bool bHasDestination{ false };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* UnitMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHealthComponent* HealthComponent;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//virtual const AActor* GetNetOwner() const override;

private:

	ABuildingBase* OwnerBuilding{ nullptr };

	class AUnitAIControllerBase* UnitController{ nullptr };

	UFUNCTION()
	void OnStopMove(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	FVector Destination{FVector::ZeroVector};

};
