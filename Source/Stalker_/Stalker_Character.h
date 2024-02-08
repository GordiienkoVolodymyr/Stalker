#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Stalker_Character.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class AWeapon;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AStalker_Character : public ACharacter
{
	GENERATED_BODY()
	
public:
	AStalker_Character();

	UFUNCTION(BlueprintCallable) //Приаттачить пушку от позиции персонажа
	void PickUp_Weapon(AWeapon* weapon);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	// Переменная для AnimBP для переключения на другой набор анимаций  
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon) bool Has_Rifle;
	
	// Pawn mesh: 1st person view (arms; seen only by self)
	//Меш игрока от первого лица (только свои руки)
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) USkeletalMeshComponent *Mesh_1P;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	AWeapon *Curennt_Weapon;

protected:
	virtual void BeginPlay();

	virtual void SetupPlayerInputComponent(UInputComponent *input_component) override;
	void Move(const FInputActionValue &value);
	void Look(const FInputActionValue &value);
	void Fire(const FInputActionValue &value);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent *FirstPersonCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext *DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *Fire_Action;
};
