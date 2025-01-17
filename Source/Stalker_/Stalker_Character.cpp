﻿// Copyright Epic Games, Inc. All Rights Reserved.

#include "Stalker_Character.h"
#include "AWeapon.h"
#include "Stalker_Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);


AStalker_Character::AStalker_Character()
{
	// Character doesnt have a rifle at start
	Has_Rifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.0f, 0.0f, 60.0f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh_1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh_1P->SetOnlyOwnerSee(true);
	Mesh_1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh_1P->bCastDynamicShadow = false;
	Mesh_1P->CastShadow = false;
	//Mesh_1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh_1P->SetRelativeLocation(FVector(-30.0f, 0.0f, -150.0f));

}

void AStalker_Character::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	// Добовляем Mapping Context для ввода
	if (APlayerController* player_controller = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem *input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer()))
		{
			input_subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}


void AStalker_Character::SetupPlayerInputComponent(UInputComponent* input_component)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(input_component))
	{
		EnhancedInputComponent->BindAction(Jump_Action, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(Jump_Action, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(Move_Action, ETriggerEvent::Triggered, this, &AStalker_Character::On_Move_Action);
		EnhancedInputComponent->BindAction(Look_Action, ETriggerEvent::Triggered, this, &AStalker_Character::On_Look_Action);
		EnhancedInputComponent->BindAction(Fire_Action, ETriggerEvent::Triggered, this, &AStalker_Character::On_Fire_Action);
		EnhancedInputComponent->BindAction(Use_Action, ETriggerEvent::Triggered, this, &AStalker_Character::On_Use_Action);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AStalker_Character::On_Move_Action(const FInputActionValue &value)
{
	// input is a Vector2D
	FVector2D movement_vector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), movement_vector.Y);
		AddMovementInput(GetActorRightVector(), movement_vector.X);
	}
}


void AStalker_Character::On_Look_Action(const FInputActionValue &value)
{
	// input is a Vector2D
	FVector2D look_axis_vector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(look_axis_vector.X);
		AddControllerPitchInput(look_axis_vector.Y);
		
	}
}

void AStalker_Character::On_Fire_Action(const FInputActionValue &value)
{
	if (Current_Weapon != 0)
	{
		Current_Weapon->Fire(this);
	}
}

void AStalker_Character::On_Use_Action(const FInputActionValue &value)
{
	int i;
	double distance, min_distance;
	AActor* item, *curr_item;
	FVector player_pos, item_pos;
	if (Interactable_Actrors.Num() == 0)
	{
		return;
	}
	if (Interactable_Actrors.Num() == 1)
	{	
		item = Interactable_Actrors[0];
		Interactable_Actrors.RemoveAt(0);
	}
	else
	{
		player_pos = GetActorLocation();

		for (i = 0; i < Interactable_Actrors.Num(); i++)
		{
			curr_item = Interactable_Actrors[i];

			item_pos = curr_item->GetActorLocation();

			distance = FVector::Distance(player_pos, item_pos);

			if (i == 0 || distance < min_distance)
			{
				min_distance = distance;
				item = curr_item;
			}
		}
		Interactable_Actrors.Remove(item);
	}

	if(AWeapon *weapon = Cast<AWeapon>(item))
	{
		PickUp_Weapon(weapon);
	}
}

void AStalker_Character::PickUp_Weapon(AWeapon* weapon)
{
	if (weapon == nullptr )
	{
		return;
	}

	if (Current_Weapon != 0)
	{
		Current_Weapon->Detach();
	}

	Current_Weapon = weapon;
	Current_Weapon->Attach(Mesh_1P);
	// Устанавливаем значение true Has_Rifle, что ы анимационный блюпринт мог переключиться на другой набор анимаций
	Has_Rifle = true;
}