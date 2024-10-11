// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityTask/AbilityTask_ActivateAbilityByTag.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"

UAbilityTask_ActivateAbilityByTag* UAbilityTask_ActivateAbilityByTag::CreateTask(UGameplayAbility* OwningAbility, AActor* ActivateTarget, FGameplayTag ActivateTag)
{
	UAbilityTask_ActivateAbilityByTag* Task = NewAbilityTask<UAbilityTask_ActivateAbilityByTag>(OwningAbility);
	Task->ActivateTarget = ActivateTarget;
	Task->ActivateTag = ActivateTag;

	return Task;
}

void UAbilityTask_ActivateAbilityByTag::Activate()
{
	Super::Activate();

	if (ActivateTarget)
	{
		TScriptInterface<IAbilitySystemInterface> ASI = ActivateTarget;
		if (ASI)
		{
			FGameplayAbilitySpecHandle AbilityHandle = ASI->GetAbilitySpecHandleByTag(ActivateTag);
			if (AbilityHandle.IsValid())
			{
				ASI->GetAbilitySystemComponent()->TryActivateAbility(AbilityHandle);
			}
		}
	}

	EndTask();
}
