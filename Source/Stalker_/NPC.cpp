#include "NPC.h"

ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true; //Включаем тик на каждого персонажа

}

void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC_Human::Attach_Weapon(USkeletalMeshComponent *character_mesh, FName arm_socket_name, AWeapon *weapon)
{
	if (weapon == nullptr )
	{
		return;
	}

	if (weapon != 0)
	{
		Current_Weapon->Detach();
	}

	Current_Weapon = weapon;
	Current_Weapon->Attach_To_Socket(character_mesh, arm_socket_name);
}
