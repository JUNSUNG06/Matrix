// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_Sprint.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemInterface.h"

#include "../Attribute/MatrixCharacterAttributeSet.h"

UGameplayAbility_Sprint::UGameplayAbility_Sprint()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbility_Sprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor);
	UCharacterMovementComponent* Movement = Character->GetCharacterMovement();

	IAbilitySystemInterface* ASInterface = Cast<IAbilitySystemInterface>(ActorInfo->AvatarActor);
	const UAttributeSet* AttributeSet = ASInterface->
		GetAbilitySystemComponent()->GetAttributeSet(UMatrixCharacterAttributeSet::StaticClass());
	const UMatrixCharacterAttributeSet* MCAttributeSet = Cast<UMatrixCharacterAttributeSet>(AttributeSet);

	float SprintSpeed = 0.0f;
	if (MCAttributeSet)
	{
		SprintSpeed = MCAttributeSet->GetMaxSprintSpeed();
		OriginSpeed = MCAttributeSet->GetMaxWalkSpeed();
	}
	else
	{
		SprintSpeed = Movement->MaxWalkSpeed * 2.5f;
		OriginSpeed = Movement->MaxWalkSpeed;
	}


	Movement->MaxWalkSpeed = SprintSpeed;
}

void UGameplayAbility_Sprint::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor);
	UCharacterMovementComponent* Movement = Character->GetCharacterMovement();

	Movement->MaxWalkSpeed = OriginSpeed;
}

void UGameplayAbility_Sprint::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
