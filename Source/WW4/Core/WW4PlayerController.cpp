

#include "WW4PlayerController.h"
#include "WW4/Component/PlayerEconomyComponent.h"
#include "WW4/Component/PlayerBaseComponent.h"
#include "WW4/Component/TechTreeComponent.h"
#include "WW4/Core/WW4PlayerState.h"


AWW4PlayerController::AWW4PlayerController()
{
	EconomyComponent = CreateDefaultSubobject<UPlayerEconomyComponent>(TEXT("EconomyComponent"));
	PlayerBaseComponent = CreateDefaultSubobject<UPlayerBaseComponent>(TEXT("PlayerBaseComponent"));
	TechTreeComponent = CreateDefaultSubobject<UTechTreeComponent>(TEXT("TechTreeComponent"));
}

void AWW4PlayerController::SetPlayerFaction_Implementation(const EFaction& InFaction)
{
	GetPlayerState<AWW4PlayerState>()->SetFaction(InFaction);
}

EFaction AWW4PlayerController::GetPlayerFaction_Implementation() const
{
	return GetPlayerState<AWW4PlayerState>()->GetFaction();
}

void AWW4PlayerController::Defeated_Implementation()
{

}