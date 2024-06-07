// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"
#include "Components/ProgressBar.h"

void UHealthBar::UpdateBar(float InPercent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(InPercent);
	}
}
