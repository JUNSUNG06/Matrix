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
	if (!OwnerMC)
	{
		UE_LOG(LogTemp, Log, TEXT("set owner mc"));
		OwnerMC = Cast<ABaseMatrixCharacter>(ActorInfo->AvatarActor);
	}
	
	if (OwnerMC)
	{
		for (int i = 0; i < ActivationOwnedTags.Num(); i++)
		{
			if (!ActivationOwnedTags.IsValidIndex(i))
				continue;

			FGameplayTag Tag = ActivationOwnedTags.GetByIndex(i);
			if (OwnerMC->AbilityActivateDelegates.Contains(Tag))
			{
				OwnerMC->AbilityActivateDelegates[Tag].Broadcast(EAbilityActivateType::Activate);
			}
		}
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UMatrixAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (IsActive())
	{
		if (OwnerMC)
		{
			for (int i = 0; i < ActivationOwnedTags.Num(); i++)
			{
				if (!ActivationOwnedTags.IsValidIndex(i))
					continue;

				FGameplayTag Tag = ActivationOwnedTags.GetByIndex(i);
				if (OwnerMC->AbilityActivateDelegates.Contains(Tag))
				{
					OwnerMC->AbilityActivateDelegates[Tag].Broadcast(EAbilityActivateType::End);
				}
			}
		}
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}