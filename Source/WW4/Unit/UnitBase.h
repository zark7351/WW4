#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4/Building/BuildingBase.h"
#include "WW4/Interface/BaseObjectInterface.h"
#include "UnitBase.generated.h"

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

	virtual void OnInit();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void EnableOutline(bool bEnable);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSelected(bool bSelected);
	virtual void OnSelected_Implementation(bool bSelected) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetTarget(AActor* Targetactor);
	virtual void SetTarget_Implementation(AActor* Targetactor) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* UnitMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHealthComponent* HealthComponent;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	ABuildingBase* OwnerBuilding{ nullptr };
};
