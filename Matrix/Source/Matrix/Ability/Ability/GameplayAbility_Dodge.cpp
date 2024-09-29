// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_Dodge.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "KismetAnimationLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MotionWarpingComponent.h"

#include "../../Character/PlayerMatrixCharacter.h"

void UGameplayAbility_Dodge::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	ACharacter* Character = Cast<ACharacter>(OwnerInfo->AvatarActor);
	FVector Direction = OwnerInfo->AvatarActor->GetVelocity().GetSafeNormal();
	FRotator Rotation;
	APlayerMatrixCharacter* Player = Cast<APlayerMatrixCharacter>(OwnerInfo->AvatarActor);

	if (Character->GetCharacterMovement()->bOrientRotationToMovement)
	{
		if (Direction == FVector::ZeroVector)
		{
			if (Player)
			{
				FRotator Rotate(0.0f,
					Player->GetController()->GetControlRotation().Yaw, 0.0f);
				Character->SetActorRotation(Rotate);
			}

			Direction = Character->GetActorForwardVector();
		}
		else
		{
			Character->SetActorRotation(Direction.Rotation());
		}

		//Rotation = OwnerInfo->AvatarActor->GetActorRotation();
	}
	else
	{

	}

	Rotation = OwnerInfo->AvatarActor->GetActorRotation();

	UMotionWarpingComponent* WarpingComp = 
		OwnerInfo->AvatarActor->GetComponentByClass<UMotionWarpingComponent>();
	if (WarpingComp)
	{
		FVector DodgePoint = Direction * DodgeDistance + OwnerInfo->AvatarActor->GetActorLocation();
		FMotionWarpingTarget Target = {};
		Target.Name = WarpPointName;
		Target.Location = DodgePoint;
		WarpingComp->AddOrUpdateWarpTarget(Target);
		DrawDebugLine(GetWorld(), OwnerInfo->AvatarActor->GetActorLocation(), DodgePoint, FColor::Blue, 1.0f);
	}
	
	float Angle = UKismetAnimationLibrary::CalculateDirection(Direction, Rotation);
	UE_LOG(LogTemp, Log, TEXT("%f"), Angle);
	if (FMath::Abs(Angle) <= 45)
	{
		MontageJumpToSection(TEXT("Forward"));
	}
	else if (45 < Angle && Angle < 135)
	{
		MontageJumpToSection(TEXT("Right"));
	}
	else if (-45 > Angle && Angle > -135)
	{
		MontageJumpToSection(TEXT("Left"));
	}
	else if (FMath::Abs(Angle) >= 135)
	{
		MontageJumpToSection(TEXT("Back"));
	}
}
