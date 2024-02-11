#include "AWeapon.h"

AWeapon::AWeapon()
{	
	Muzzle_Offset = FVector(100.0f, 0.0f, 10.0f); // Смещение по умолчанию от персонажа до точки спавна снаряда
}

void AWeapon::Detach()
{
	USceneComponent *root_conponent = GetRootComponent();

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	
	if (UPrimitiveComponent *primitive_component = Cast<UPrimitiveComponent>(root_conponent))
	{
		primitive_component->SetSimulatePhysics(true);
		primitive_component->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	}
}

void AWeapon::Attach(USkeletalMeshComponent *arms_mesh)
{
	
	USceneComponent *root_conponent = GetRootComponent();
	if (UPrimitiveComponent *primitive_component = Cast<UPrimitiveComponent>(root_conponent))
	{
		primitive_component->SetSimulatePhysics(false);
		primitive_component->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	}

	// Аттачим оружие к персонажу
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(arms_mesh, AttachmentRules, FName(TEXT("GripPoint")));

}

void AWeapon::Fire(AStalker_Character* character)
{
	if (character == nullptr || character->GetController() == nullptr)
	{
		return;
	}

	//Пытаемся выстрелить снарядом
	if (Projectile_Class != nullptr)
	{
		if (UWorld* const world = GetWorld())
		{
			APlayerController* player_controller = Cast<APlayerController>(character->GetController());
			FRotator spawn_rotation = player_controller->PlayerCameraManager->GetCameraRotation();
			//Muzzle_Offset представлен в пространстве камеры, его надо перевести в мировое пространство прежде, чем смещать от позиции персонажа для того что бы найти позицию дула
			FVector spawn_location = GetActorLocation() + spawn_rotation.RotateVector(Muzzle_Offset);

			//Устанавливаем оброботку столкновений при спавне
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// Спавним снаряд на дуле
			world->SpawnActor<AStalker_Projectile>(Projectile_Class, spawn_location, spawn_rotation, ActorSpawnParams);
		}
	}

	// Пытаемся проиграть звук выстрела если он указан
	if (Fire_Sound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Fire_Sound, character->GetActorLocation());
	}

	// Пытаемся проиграть анимацию выстрела если он указан
	/*if (Fire_Animation != nullptr)
	{
		if (UAnimInstance* anim_instance = character->Mesh_1P->GetAnimInstance())
		{
			anim_instance->Montage_Play(Fire_Animation, 1.0f);
		}
	}*/
}

void AWeapon::Attach_To_Socket(USkeletalMeshComponent *character_mesh, FName arm_socket_name)
{

	USceneComponent *root_conponent = GetRootComponent();
	if (UPrimitiveComponent *primitive_component = Cast<UPrimitiveComponent>(root_conponent))
	{
		primitive_component->SetSimulatePhysics(false);
		primitive_component->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	}

	// Аттачим оружие к персонажу
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(character_mesh, AttachmentRules, arm_socket_name);

}

void AWeapon::Fire_NPC()
{
	if (Fire_Animation != 0)
	{
		BP_Weapon_Mesh_Component->PlayAnimation(Fire_Animation, false);
	}
}