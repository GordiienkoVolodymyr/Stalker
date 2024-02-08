#include "AWeapon.h"

AWeapon::AWeapon()
{	
	Muzzle_Offset = FVector(100.0f, 0.0f, 10.0f); // �������� �� ��������� �� ��������� �� ����� ������ �������
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

	//�������� ���������� ��������
	if (Projectile_Class != nullptr)
	{
		if (UWorld* const world = GetWorld())
		{
			APlayerController* player_controller = Cast<APlayerController>(character->GetController());
			FRotator spawn_rotation = player_controller->PlayerCameraManager->GetCameraRotation();
			//Muzzle_Offset ����������� � ������������ ������, ��� ���� ��������� � ������� ������������ ������, ��� ������� �� ������� ��������� ��� ���� ��� �� ����� ������� ����
			FVector spawn_location = GetOwner()->GetActorLocation() + spawn_rotation.RotateVector(Muzzle_Offset);

			//������������� ��������� ������������ ��� ������
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// ������� ������ �� ����
			world->SpawnActor<AStalker_Projectile>(Projectile_Class, spawn_location, spawn_rotation, ActorSpawnParams);
		}
	}

	// �������� ��������� ���� �������� ���� �� ������
	if (Fire_Sound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Fire_Sound, character->GetActorLocation());
	}

	// �������� ��������� �������� �������� ���� �� ������
	if (Fire_Animation != nullptr)
	{
		if (UAnimInstance* anim_instance = character->Mesh_1P->GetAnimInstance())
		{
			anim_instance->Montage_Play(Fire_Animation, 1.0f);
		}
	}
}