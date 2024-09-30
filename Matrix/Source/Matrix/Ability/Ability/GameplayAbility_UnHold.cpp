// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_UnHold.h"

#include "../../Interface/ItemHoldInterface.h"
#include "../../Component/ItemHoldComponent.h"

UGameplayAbility_UnHold::UGameplayAbility_UnHold()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbility_UnHold::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	IItemHoldInterface* Interface = Cast<IItemHoldInterface>(ActorInfo->AvatarActor);
	if (Interface)
	{
		UItemHoldComponent* ItemHold = Interface->GetItemHoldComponent();
		if (ItemHold)
		{
			ItemHold->UnHold();
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
