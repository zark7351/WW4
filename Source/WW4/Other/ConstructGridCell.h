// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "ConstructGridCell.generated.h"

/**
 * 
 */
UCLASS()
class WW4_API AConstructGridCell : public ADecalActor
{
	GENERATED_BODY()

public:

	AConstructGridCell();

	UPROPERTY()
	bool bEnabled{ true };

	UPROPERTY()
	bool bBlock{ false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* GreenMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* RedMaterial;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds)override;

private:

	bool CurStyle{ false };

	void SetStyle(bool bBlocked);

	bool TraceBlock();
};
