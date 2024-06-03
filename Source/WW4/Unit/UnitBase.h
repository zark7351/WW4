#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WW4/BaseTypes/BaseTypes.h"
#include "WW4/Building/BuildingBase.h"
#include "UnitBase.generated.h"

UCLASS()
class WW4_API AUnitBase : public APawn
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
