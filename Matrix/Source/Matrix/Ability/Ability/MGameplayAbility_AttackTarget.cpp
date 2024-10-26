// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/MGameplayAbility_AttackTarget.h"
#include "../../Character/BaseMatrixCharacter.h"

bool UMGameplayAbility_AttackTarget::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
		return false;

	ABaseMatrixCharacter* MC = Cast<ABaseMatrixCharacter>(ActorInfo->AvatarActor);
	if (!MC)
		return false;
	if (!MC->GetTarget())
		return false;

	return true;
}

void UMGameplayAbility_AttackTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FGameplayEffectSpecHandle EffectHandle =
		MakeOutgoingGameplayEffectSpec(Effect, TriggerEventData->EventMagnitude);

	if (EffectHandle.IsValid())
	{
		FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();
		TargetData->SetActors({ OwnerMC->GetTarget()});
		FGameplayAbilityTargetDataHandle DataHandle(TargetData);

		ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo,
			CurrentActivationInfo, EffectHandle, DataHandle);
	}
		
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
