// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_BlockParryAttack.h"

#include "../../Character/BaseMatrixCharacter.h"

void UGameplayAbility_BlockParryAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (OwnerMC->GetTarget())
	{
		FGameplayEffectSpecHandle EffectHandle =
			MakeOutgoingGameplayEffectSpec(WarningEffect);
		if (EffectHandle.IsValid())
		{
			FGameplayAbilityTargetData* TargetData = new FGameplayAbilityTargetData();
			TargetData->SetActors({ OwnerMC->GetTarget() });
			FGameplayAbilityTargetDataHandle TargetDataHandle(TargetData);

			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo,
				CurrentActivationInfo, EffectHandle, TargetDataHandle);
		}
	}
}
