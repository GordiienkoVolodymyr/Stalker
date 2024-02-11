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

	// Переменная для AnimBP для переключения на другой набор анимаций  
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon) bool Has_Rifle;
	
	//Меш игрока от первого лица (только свои руки)
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) USkeletalMeshComponent *Mesh_1P;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly) AWeapon *Current_Weapon;

protected:
	virtual void BeginPlay();
	virtual void SetupPlayerInputComponent(UInputComponent *input_component) override;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly) TArray<AActor*> Interactable_Actrors;


private:

	void On_Move_Action(const FInputActionValue &value);
	void On_Look_Action(const FInputActionValue &value);
	void On_Fire_Action(const FInputActionValue &value);
	void On_Use_Action(const FInputActionValue &value);
	void PickUp_Weapon(AWeapon* weapon); //Приаттачить пушку от позиции персонажа


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent *FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext *DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *Jump_Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *Move_Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Look_Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *Fire_Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *Use_Action;
};
