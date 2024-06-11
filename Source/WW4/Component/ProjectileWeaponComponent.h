//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "WeaponComponent.h"
//#include "ProjectileWeaponComponent.generated.h"
//
///**
// * 
// */
//UCLASS(Blueprintable)
//class WW4_API UProjectileWeaponComponent : public UWeaponComponent
//{
//	GENERATED_BODY()
//
//public:
//
//	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
//	void Fire();
//
//	void Fire_Implementation() override;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	TSubclassOf<AProjectileBase> ProjectileClass;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool  bOverrideProjectileSpeed{ true };
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bOverrideProjectileSpeed"))
//	float ProjectileSpeedOverride{ 2000.f };
//
//
//	UFUNCTION(BlueprintCallable)
//	float GetProjectileSpeed() const;
//
//	UFUNCTION(BlueprintCallable)
//	float GetProjectileRadius() const;
//};
