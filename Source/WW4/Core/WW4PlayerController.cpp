

#include "WW4PlayerController.h"
#include "WW4/Component/PlayerEconomyComponent.h"
#include "WW4/Component/PlayerBaseComponent.h"
#include "WW4/Component/TechTreeComponent.h"


AWW4PlayerController::AWW4PlayerController()
{
	EconomyComponent = CreateDefaultSubobject<UPlayerEconomyComponent>(TEXT("EconomyComponent"));
	PlayerBaseComponent = CreateDefaultSubobject<UPlayerBaseComponent>(TEXT("PlayerBaseComponent"));
	TechTreeComponent = CreateDefaultSubobject<UTechTreeComponent>(TEXT("TechTreeComponent"));
}

void AWW4PlayerController::SetPlayerFaction_Implementation(const EFaction& InFaction)
{
	PlayerBaseComponent->SetFaction(InFaction);
}

EFaction AWW4PlayerController::GetPlayerFaction_Implementation() const
{
	return PlayerBaseComponent->GetFaction();
}

void AWW4PlayerController::Defeated_Implementation()
{

}