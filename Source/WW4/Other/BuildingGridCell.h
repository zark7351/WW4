// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BuildingGridCell.generated.h"

/**
 * 
 */
UCLASS()
class WW4_API ABuildingGridCell : public AStaticMeshActor
{
	GENERATED_BODY()
	

public:
	
	UPROPERTY()
	bool bEnabled{true};

	UPROPERTY()
	bool bBlock{false};

protected:

	virtual void Tick(float DeltaSeconds)override;

private:

	bool CurStyle{ false };

	void SetStyle(bool bBlocked);

	bool TraceBlock();
};
