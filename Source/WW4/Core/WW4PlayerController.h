
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

UCLASS()
class WW4_API AWW4PlayerController : public APlayerController, public IBasePlayerInterface
{
	GENERATED_BODY()
	
public:

	AWW4PlayerController();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Defeated();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerEconomyComponent* EconomyComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerBaseComponent* PlayerBaseComponent;

	virtual void SetPlayerFaction_Implementation(const EFaction& InFaction) override;
	virtual EFaction GetPlayerFaction_Implementation() const override;
};
