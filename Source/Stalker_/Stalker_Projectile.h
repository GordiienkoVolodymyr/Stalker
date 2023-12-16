// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stalker_Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class AStalker_Projectile : public AActor
{
	GENERATED_BODY()

public:
	AStalker_Projectile();

	// called when projectile hits something 
	//вызываеться когда снаряд удариться во что-то
	UFUNCTION()
	void On_Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile) USphereComponent *Collision_Comp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent *Projectile_Movement;
};

