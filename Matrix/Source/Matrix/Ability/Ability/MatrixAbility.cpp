// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/MatrixAbility.h"
#include "../../Character/BaseMatrixCharacter.h"

UMatrixAbility::UMatrixAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UMatrixAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
		return false;

	ABaseMatrixCharacter* MC = Cast<ABaseMatrixCharacter>(ActorInfo->AvatarActor);
	if (!MC)
		return false;

	return true;
}

void UMatrixAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	OwnerMC = Cast<ABaseMatrixCharacter>(ActorInfo->AvatarActor);
}