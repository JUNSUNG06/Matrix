// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_Katana_Attack.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "../AbilityTask/AbilityTask_ActivateAbilityByTag.h"
#include "../AbilityTask/GAAT_ActivateAbilityTargetHasTag.h"
#include "../AbilityTask/GAAT_TraceTarget.h"
#include "../TargetActor/GATA_SphereTrace.h"
#include "../../Character/BaseMatrixCharacter.h"

UGameplayAbility_Katana_Attack::UGameplayAbility_Katana_Attack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UGameplayAbility_Katana_Attack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if(!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
		return false;

	ABaseMatrixCharacter* BMC = Cast<ABaseMatrixCharacter>(ActorInfo->AvatarActor);
	if (!BMC)
		return false;
	
	return true;
}

void UGameplayAbility_Katana_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UGAAT_TraceTarget* TraceTask = UGAAT_TraceTarget::CreateTask(this, AGATA_SphereTrace::StaticClass());
	TraceTask->SetTraceData(CheckEnemyRange, CheckEnemyRadius);
	TraceTask->OnComplete.AddDynamic(this, &UGameplayAbility_Katana_Attack::CompleteTraceTask);
	TraceTask->ReadyForActivation();
}

void UGameplayAbility_Katana_Attack::CompleteTraceTask(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	//clutch attack
	for (int i = 0; i < TargetDataHandle.Data.Num(); i++)
	{
		TSharedPtr<FGameplayAbilityTargetData> Target = TargetDataHandle.Data[i];
		const FHitResult* HitResult = Target->GetHitResult();
		if (!HitResult)
			continue;
		AActor* TargetActor = HitResult->GetActor();
		if (!TargetActor)
			continue;

		TScriptInterface<IAbilitySystemInterface> TargetASI = TargetActor;
		if (!TargetASI)
			continue;

		UAbilitySystemComponent* TargetASC = TargetASI->GetAbilitySystemComponent();
		if (!TargetASC->GetOwnedGameplayTags().HasTag(StunTag))
			continue;
		
		ABaseMatrixCharacter* BMC = Cast<ABaseMatrixCharacter>(GetAvatarActorFromActorInfo());
		BMC->Target = TargetActor;

		TScriptInterface<IAbilitySystemInterface> OwnerASI = GetAvatarActorFromActorInfo();
		FGameplayAbilitySpecHandle AbilityHandle = OwnerASI->GetAbilitySpecHandleByTag(StunClutchAttackTag);
		if (AbilityHandle.IsValid())
		{
			OwnerASI->GetAbilitySystemComponent()->TryActivateAbility(AbilityHandle);
		}

		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return;
	}

	TScriptInterface<IAbilitySystemInterface> OwnerASI = GetAvatarActorFromActorInfo();
	FGameplayAbilitySpecHandle AbilityHandle = OwnerASI->GetAbilitySpecHandleByTag(ComboAttackTag);
	if (AbilityHandle.IsValid())
	{
		OwnerASI->GetAbilitySystemComponent()->TryActivateAbility(AbilityHandle);
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}