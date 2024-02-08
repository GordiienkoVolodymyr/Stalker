#pragma once

#include "Stalker_Character.h"
#include "Stalker_Projectile.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "AWeapon.generated.h"

UCLASS()
class STALKER__API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	void Detach();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* Fire_Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* Fire_Animation;

	//Смещение дула пушки от позиции персонажа
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector Muzzle_Offset;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	//UInputMappingContext* Fire_Mapping_Context;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	//UInputAction* Fire_Action;

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AStalker_Projectile> Projectile_Class;

	UFUNCTION(BlueprintCallable, Category="Weapon") //Выстрелить снарядом
	void Fire(AStalker_Character* character);

};
