// Copyright Epic Games, Inc. All Rights Reserved.

#include "Stalker_Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AStalker_Projectile::AStalker_Projectile() 
{
	// Use a sphere as a simple collision representation
	Collision_Comp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	Collision_Comp->InitSphereRadius(5.0f);
	Collision_Comp->BodyInstance.SetCollisionProfileName("Projectile");
	Collision_Comp->OnComponentHit.AddDynamic(this, &AStalker_Projectile::On_Hit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	Collision_Comp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.0f));
	Collision_Comp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = Collision_Comp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	Projectile_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	Projectile_Movement->UpdatedComponent = Collision_Comp;
	Projectile_Movement->InitialSpeed = 3000.0f;
	Projectile_Movement->MaxSpeed = 3000.0f;
	Projectile_Movement->bRotationFollowsVelocity = true;
	Projectile_Movement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AStalker_Projectile::On_Hit(UPrimitiveComponent* hit_comp, AActor* other_actor, UPrimitiveComponent* other_comp, FVector normal_impulse, const FHitResult& hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((other_actor != nullptr) && (other_actor != this) && (other_comp != nullptr) && other_comp->IsSimulatingPhysics())
	{
		other_comp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}