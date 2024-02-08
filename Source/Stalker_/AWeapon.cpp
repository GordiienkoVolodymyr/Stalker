#include "AWeapon.h"

AWeapon::AWeapon()
{	
	Muzzle_Offset = FVector(100.0f, 0.0f, 10.0f); // Смещение по умолчанию от персонажа до точки спавна снаряда
}

void AWeapon::Detach()
{

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
			FVector spawn_location = GetOwner()->GetActorLocation() + spawn_rotation.RotateVector(Muzzle_Offset);

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
	if (Fire_Animation != nullptr)
	{
		if (UAnimInstance* anim_instance = character->Mesh_1P->GetAnimInstance())
		{
			anim_instance->Montage_Play(Fire_Animation, 1.0f);
		}
	}
}