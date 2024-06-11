//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "ProjectileWeaponComponent.h"
//#include "WW4/Projectile/ProjectileBase.h"
//#include "GameFramework/ProjectileMovementComponent.h"
//#include "Components/SphereComponent.h"
//
//void UProjectileWeaponComponent::Fire_Implementation()
//{
//	if (GetOwner()->HasAuthority())
//	{
//		FTransform Transform;
//		Transform.SetLocation(GetComponentLocation());
//		Transform.SetRotation(GetComponentQuat());
//		AProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileBase>(ProjectileClass, Transform);
//		if (Projectile)
//		{
//			if (bOverrideProjectileSpeed)
//			{
//				Projectile->SetProjectileSpeedOverride(ProjectileSpeedOverride);
//			}
//			Projectile->FinishSpawning(Transform);
//		}
//	}
//}
//
//float UProjectileWeaponComponent::GetProjectileSpeed() const
//{
//	if (ProjectileClass)
//	{
//		AProjectileBase* CDO = Cast<AProjectileBase>(ProjectileClass->GetDefaultObject());
//		if (CDO && CDO->ProjectileMovement)
//		{
//			return bOverrideProjectileSpeed? ProjectileSpeedOverride : CDO->ProjectileMovement->GetMaxSpeed();
//		}
//	}
//	return 0.0f;
//}
//
//float UProjectileWeaponComponent::GetProjectileRadius() const
//{
//	if (ProjectileClass)
//	{
//		AProjectileBase* CDO = Cast<AProjectileBase>(ProjectileClass->GetDefaultObject());
//		if (CDO && CDO->CollisionSphere)
//		{
//			return CDO->CollisionSphere->GetScaledSphereRadius();
//		}
//	}
//	return 0.0f;
//}
