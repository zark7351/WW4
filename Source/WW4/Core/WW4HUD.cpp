// Fill out your copyright notice in the Description page of Project Settings.


#include "WW4HUD.h"
#include "EngineUtils.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Slate/SlateBrushAsset.h"
#include "WW4/Unit/UnitBase.h"
#include "Components/BoxComponent.h"

void AWW4HUD::GetUnitsInSelectionRectangle(const FVector2D& FirstPoint, const FVector2D& SecondPoint, TArray<AUnitBase*>& OutUnits, bool bActorMustBeFullyEnclosed)
{
	// Because this is a HUD function it is likely to get called each tick,
		// so make sure any previous contents of the out actor array have been cleared!
	OutUnits.Reset();

	//Create Selection Rectangle from Points
	FBox2D SelectionRectangle(ForceInit);

	//This method ensures that an appropriate rectangle is generated, 
	//		no matter what the coordinates of first and second point actually are.
	SelectionRectangle += FirstPoint;
	SelectionRectangle += SecondPoint;


	//The Actor Bounds Point Mapping
	const FVector BoundsPointMapping[8] =
	{
		FVector(1.f, 1.f, 1.f),
		FVector(1.f, 1.f, -1.f),
		FVector(1.f, -1.f, 1.f),
		FVector(1.f, -1.f, -1.f),
		FVector(-1.f, 1.f, 1.f),
		FVector(-1.f, 1.f, -1.f),
		FVector(-1.f, -1.f, 1.f),
		FVector(-1.f, -1.f, -1.f) };

	//~~~

	//For Each Actor of the Class Filter Type
	for (TActorIterator<AUnitBase> Itr(GetWorld(), AUnitBase::StaticClass()); Itr; ++Itr)
	{
		AUnitBase* EachUnit = *Itr;

		//Center
		const FVector UnitCenter = EachUnit->CollisionBox->Bounds.Origin;

		//Extents
		const FVector UnitExtent = FVector(50.f,50.f,50.f);

		// Build 2D bounding box of actor in screen space
		FBox2D ActorBox2D(ForceInit);
		for (uint8 BoundsPointItr = 0; BoundsPointItr < 8; BoundsPointItr++)
		{
			// Project vert into screen space.
			const FVector ProjectedWorldLocation = Project(UnitCenter + (BoundsPointMapping[BoundsPointItr] * UnitExtent), true);
			// Add to 2D bounding box if point is on the front side of the camera
			if (ProjectedWorldLocation.Z > 0.f)
			{
				ActorBox2D += FVector2D(ProjectedWorldLocation.X, ProjectedWorldLocation.Y);
			}
		}
		// Only consider actor boxes that have valid points inside
		if (ActorBox2D.bIsValid)
		{
			//Selection Box must fully enclose the Projected Actor Bounds
			if (bActorMustBeFullyEnclosed)
			{
				if (SelectionRectangle.IsInside(ActorBox2D))
				{
					OutUnits.Add(EachUnit);
					FLinearColor Color1 = FLinearColor::Green;
					Color1.A = 0.3f;
					FLinearColor Color2 = FLinearColor::White;
					Color2.A = 0.3f;
					//DrawRect(Color2, SelectionRectangle.GetCenter().X- SelectionRectangle.GetSize().X/2, SelectionRectangle.GetCenter().Y- SelectionRectangle.GetSize().Y/2, SelectionRectangle.GetSize().X, SelectionRectangle.GetSize().Y);
					//DrawRect(Color1, ActorBox2D.GetCenter().X - ActorBox2D.GetSize().X/2, ActorBox2D.GetCenter().Y - ActorBox2D.GetSize().Y/2, ActorBox2D.GetSize().X, ActorBox2D.GetSize().Y);
				}
			}
			//Partial Intersection with Projected Actor Bounds
			else if (SelectionRectangle.Intersect(ActorBox2D))
			{
				OutUnits.Add(EachUnit);
			}
		}
	}
}