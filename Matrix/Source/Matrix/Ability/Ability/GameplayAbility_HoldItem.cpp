// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_HoldItem.h"

#include "../../Interface/ItemHoldInterface.h"
#include "../../Component/ItemHoldComponent.h"
#include "../../Interface/Equipment.h"
#include "../../Interface/Hold.h"

UGameplayAbility_HoldItem::UGameplayAbility_HoldItem()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbility_HoldItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	IItemHoldInterface* Interface = Cast<IItemHoldInterface>(ActorInfo->AvatarActor);
	if (Interface)
	{
		UItemHoldComponent* ItemHold = Interface->GetItemHoldComponent();
		if (ItemHold)
		{
			TScriptInterface<IEquipment> Equip = ItemHold->GetEquipment(TargetIndex);
			if (Equip)
			{
				TScriptInterface<IHold> Hold = Equip->GetEquipActor();
				if (Hold)
				{
					ItemHold->Hold(Hold);
				}
			}
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
