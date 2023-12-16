#include "TP_Pick_UpComponent.h"

UTP_Pick_UpComponent::UTP_Pick_UpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.0f;
}

void UTP_Pick_UpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	// Регестрируем событие пересечения (Overlap Event)
	OnComponentBeginOverlap.AddDynamic(this, &UTP_Pick_UpComponent::On_Sphere_Begin_Overlap);
}

void UTP_Pick_UpComponent::On_Sphere_Begin_Overlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_comp, int32 other_body_index, bool from_sweep, const FHitResult& sweep_result)
{
	// Checking if it is a First Person Character overlapping
	// Проверяем пересеклись ли с персонажем от первого лица 
	AStalker_Character* character = Cast<AStalker_Character>(other_actor);
	if(character != nullptr)
	{
		// Notify that the actor is being picked up
		// Уведомляем что актора подбирают
		On_Pick_Up.Broadcast(character);

		// Unregister from the Overlap Event so it is no longer triggered
		// Снимаем регестрацию на событие пересечения (Overlap Event), что бы оно больше не триггерилось 
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
