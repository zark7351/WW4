// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "WW4/UI/HealthBar.h"

PRAGMA_DISABLE_OPTIMIZATION

UHealthComponent::UHealthComponent()
{
	static ConstructorHelpers::FClassFinder<UHealthBar>HealthBarClass(TEXT("Blueprint'/Game/WW4/Blueprint/UI/WBP_HealthBar.WBP_HealthBar_C'"));
	if (HealthBarClass.Succeeded())
	{
		SetWidgetClass(HealthBarClass.Class);
	}
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawAtDesiredSize(true);
	UpdateHealth();
	SetVisibility(false);
}

void UHealthComponent::ShowHealthBar(bool bShow)
{
	if (bShow != bShowing)
	{
		SetVisibility(bShow);
		bShowing = bShow;
	}
}

void UHealthComponent::UpdateHealth()
{
	HealthBar = HealthBar == nullptr ? Cast<UHealthBar>(GetWidget()) : HealthBar;
	if (HealthBar)
	{
		float Percentage = CurrentHealth / MaxHealth;
		HealthBar->UpdateBar(Percentage);
	}
}

float UHealthComponent::OnTakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!bShowing)
	{
		ShowHealthBar(true);
	}
	float FinalDamage = DamageAmount * (1 - Armor / 100.f);
	CurrentHealth = FMath::Clamp(CurrentHealth - FinalDamage, 0.f, MaxHealth);
	UpdateHealth();
	if (CurrentHealth <= 0.f)
	{
		GetOwner()->Destroy();
	}
	return FinalDamage;
}

PRAGMA_ENABLE_OPTIMIZATION