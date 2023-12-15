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

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AStalker_Character : public ACharacter
{
	GENERATED_BODY()
	
public:
	AStalker_Character();

	//USkeletalMeshComponent *Get_Mesh_1P() const { return Mesh_1P; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	// ���������� ��� AnimBP ��� ������������ �� ������ ����� ��������  
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon) bool Has_Rifle;
	
	// Pawn mesh: 1st person view (arms; seen only by self)
	//��� ������ �� ������� ���� (������ ���� ����)
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) USkeletalMeshComponent *Mesh_1P;

protected:
	virtual void BeginPlay();

	virtual void SetupPlayerInputComponent(UInputComponent *input_component) override;
	void Move(const FInputActionValue &value);
	void Look(const FInputActionValue &value);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent *FirstPersonCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext *DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *MoveAction;
};
