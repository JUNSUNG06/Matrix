// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstance/MatrixAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "../../Interface/ItemHoldInterface.h"
#include "../../Component/ItemHoldComponent.h"

void UMatrixAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(GetOwningActor());
	if (Character)
	{
		Movement = Character->GetCharacterMovement();
	}
}

void UMatrixAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character)
	{
		IItemHoldInterface* ItemHoldInterface = Cast<IItemHoldInterface>(Character);
		if (ItemHoldInterface)
		{
			UItemHoldComponent* ItemHoldComp = ItemHoldInterface->GetItemHoldComponent();

			ItemHoldType = ItemHoldComp->GetCurrentHoldType();
		}
	}

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bShouldMove = (Movement->GetCurrentAcceleration() != FVector(0.0f, 0.0f, 0.0f)) && (GroundSpeed > 3.0f);
		bIsFalling = Movement->IsFalling();
	}
}
