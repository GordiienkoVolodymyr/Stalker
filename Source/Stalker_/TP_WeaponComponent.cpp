// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "Stalker_Character.h"
#include "Stalker_Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f); // �������� �� ��������� �� ��������� �� ����� ������ �������
}


void UTP_WeaponComponent::AttachWeapon(AStalker_Character* target_character)
{
	Character = target_character;

	// Check that the character is valid, and has no rifle yet
	if (Character == nullptr || Character->Has_Rifle)
	{
		return;
	}

	// ������� ������ � ���������
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->Mesh_1P, AttachmentRules, FName(TEXT("GripPoint")));
	// ������������� �������� true Has_Rifle, ��� � ������������ �������� ��� ������������� �� ������ ����� ��������
	Character->Has_Rifle = true;

	// ������������� ������� ��������
	if (APlayerController* player_controller = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer()))
		{
			// ������������� ��������� ������� � 1, ��� ��������� �������� Jump ��������� Fire ��� ������������ ����� � ���������
			input_subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* enhanced_input_component = Cast<UEnhancedInputComponent>(player_controller->InputComponent))
		{
			// Fire
			enhanced_input_component->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
		}
	}
}


void UTP_WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	//�������� ���������� ��������
	if (ProjectileClass != nullptr)
	{
		if (UWorld* const world = GetWorld())
		{
			APlayerController* player_controller = Cast<APlayerController>(Character->GetController());
			FRotator spawn_rotation = player_controller->PlayerCameraManager->GetCameraRotation();
			//MuzzleOffset ����������� � ������������ ������, ��� ���� ��������� � ������� ������������ ������, ��� ������� �� ������� ��������� ��� ���� ��� �� ����� ������� ����
			FVector spawn_location = GetOwner()->GetActorLocation() + spawn_rotation.RotateVector(MuzzleOffset);

			//������������� ��������� ������������ ��� ������
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// ������� ������ �� ����
			world->SpawnActor<AStalker_Projectile>(ProjectileClass, spawn_location, spawn_rotation, ActorSpawnParams);
		}
	}
	
	// �������� ��������� ���� �������� ���� �� ������
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// �������� ��������� �������� �������� ���� �� ������
	if (FireAnimation != nullptr)
	{
		if (UAnimInstance* anim_instance = Character->Mesh_1P->GetAnimInstance())
		{
			anim_instance->Montage_Play(FireAnimation, 1.0f);
		}
	}
}


void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type end_play_reason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* player_controller = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer()))
		{
			input_subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}