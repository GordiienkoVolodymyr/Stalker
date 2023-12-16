#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Stalker_Character.h"
#include "TP_Pick_UpComponent.generated.h"

// Declaration of the delegate that will be called when someone picks this up
// The character picking this up is the parameter sent with the notification
//���������� ��������, ������� ����� ������, ����� ���-�� �������� ���� �������
// ��������, ����������� ���� ������, ����� ������� ��� �������� �����������
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Pick_Up, AStalker_Character*, PickUpCharacter);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STALKER__API UTP_Pick_UpComponent : public USphereComponent
{
	GENERATED_BODY()

public:

	UTP_Pick_UpComponent();

	// Delegate to whom anyone can subscribe to receive this event 
	//������� �� ������� ����� ����������� ���-�� ������ � �������� ��� �������
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOn_Pick_Up On_Pick_Up;

protected:

	virtual void BeginPlay() override;

	//Code for when something overlaps this component 
	UFUNCTION()
	void On_Sphere_Begin_Overlap(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_comp, int32 other_body_index, bool from_sweep, const FHitResult &sweep_result);
};