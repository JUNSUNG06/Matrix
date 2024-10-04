// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_Guard.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"


UGameplayAbility_Guard::UGameplayAbility_Guard()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbility_Guard::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, TEXT("PlayGuard"), GuardMontage, 1.0f, NAME_None, false);
	
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor);
	if (Character->GetCharacterMovement()->bOrientRotationToMovement)
	{
		FRotator Rotate(0.0f,
			Character->GetController()->GetControlRotation().Yaw, 0.0f);
		Character->SetActorRotation(Rotate);
	}
	
	MontageTask->OnCompleted.AddDynamic(this, &UGameplayAbility_Guard::OnCompleteCallback);
	MontageTask->OnInterrupted.AddDynamic(this, &UGameplayAbility_Guard::InterruptedCallback);
	MontageTask->OnCancelled.AddDynamic(this, &UGameplayAbility_Guard::CanceledCallback);
	MontageTask->ReadyForActivation();
}

void UGameplayAbility_Guard::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	MontageJumpToSection(TEXT("End"));
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_Guard::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,
		bReplicatedEndAbility, bWasCancelled);
}

void UGameplayAbility_Guard::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,
		bReplicatedEndAbility, bWasCancelled);
}

void UGameplayAbility_Guard::InterruptedCallback()
{
	MontageStop();
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,
		bReplicatedEndAbility, bWasCancelled);
}

void UGameplayAbility_Guard::CanceledCallback()
{
	MontageStop();
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,
		bReplicatedEndAbility, bWasCancelled);
}
