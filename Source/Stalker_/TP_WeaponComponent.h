// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Stalker_Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STALKER__API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UTP_WeaponComponent();

	UFUNCTION(BlueprintCallable, Category="Weapon") //Приаттачить пушку от позиции персонажа
	void AttachWeapon(AStalker_Character* target_character);

	UFUNCTION(BlueprintCallable, Category="Weapon") //Выстрелить снарядом
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AStalker_Projectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	//Смещение дула пушки от позиции персонажа
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* FireAction;

protected:
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type end_play_reason) override;

private:
	/** The Character holding this weapon*/
	AStalker_Character* Character; // Персонаж который держит это оружие
};
