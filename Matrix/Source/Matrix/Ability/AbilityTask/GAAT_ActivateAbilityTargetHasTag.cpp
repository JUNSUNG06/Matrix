// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityTask/GAAT_ActivateAbilityTargetHasTag.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

UGAAT_ActivateAbilityTargetHasTag* UGAAT_ActivateAbilityTargetHasTag::CreateTask(UGameplayAbility* OwningAbility, AActor* ActivateTarget, FGameplayTag AcrivateTag, AActor* CheckTarget, FGameplayTag CheckTag)
{
	UGAAT_ActivateAbilityTargetHasTag* Task = NewAbilityTask<UGAAT_ActivateAbilityTargetHasTag>(OwningAbility);
	Task->ActivateTarget = ActivateTarget;
	Task->ActivateTag = AcrivateTag;
	Task->CheckTarget = CheckTarget;
	Task->CheckTag = CheckTag;

	return Task;
}

void UGAAT_ActivateAbilityTargetHasTag::Activate()
{
	TScriptInterface<IAbilitySystemInterface> ASI = CheckTarget;
	if (!ASI)
		return;

	UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();
	if (!ASC->GetOwnedGameplayTags().HasTag(CheckTag))
		return;

	Super::Activate();
}
