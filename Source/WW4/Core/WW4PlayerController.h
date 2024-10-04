
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WW4/Interface/BasePlayerInterface.h"
#include "WW4PlayerController.generated.h"

/**
 * 
 */

class UPlayerEconomyComponent;
class UPlayerBaseComponent;
class UTechTreeComponent;

UCLASS()
class WW4_API AWW4PlayerController : public APlayerController, public IBasePlayerInterface
{
	GENERATED_BODY()
	
public:

	AWW4PlayerController();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AWW4PlayerState* GetWW4PlayerState() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Defeated();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerBaseComponent* PlayerBaseComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerEconomyComponent* EconomyComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTechTreeComponent* TechTreeComponent;

	virtual void SetPlayerFaction_Implementation(const EFaction& InFaction) override;
	virtual EFaction GetPlayerFaction_Implementation() const override;
};
