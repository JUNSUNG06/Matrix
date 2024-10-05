// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_AttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"

#include "../AbilityTask/GAAT_TraceTarget.h"
#include "../TargetActor/GATA_SphereTrace.h"

UGameplayAbility_AttackHitCheck::UGameplayAbility_AttackHitCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbility_AttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	UGAAT_TraceTarget* TraceTask = UGAAT_TraceTarget::CreateTask(this,
		AGATA_SphereTrace::StaticClass());
	TraceTask->OnComplete.AddDynamic(this,
		&UGameplayAbility_AttackHitCheck::OnTraceResultCallback);
	TraceTask->SetTraceData(TraceRange, TraceRadius);
	TraceTask->ReadyForActivation();
}

void UGameplayAbility_AttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	for (int i = 0; i < TargetDataHandle.Num(); i++)
	{
		auto Data = TargetDataHandle.Data[i];
		AActor* DetectActor = Data->GetHitResult()->GetActor();

		UAbilitySystemComponent* TargetASC =
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(DetectActor);
		if (TargetASC)
		{
			FGameplayEffectSpecHandle EffectHandle =
				MakeOutgoingGameplayEffectSpec(AttackDamageEffect);
			if (EffectHandle.IsValid())
			{
				ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo,
					CurrentActivationInfo, EffectHandle, TargetDataHandle);
			}
		}
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
