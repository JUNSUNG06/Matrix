// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_Parry.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

#include "../AbilityTask/GAAT_TraceTarget.h"
#include "../TargetActor/GATA_SphereTrace.h"

void UGameplayAbility_Parry::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	UGAAT_TraceTarget* TraceTask = UGAAT_TraceTarget::CreateTask(this,
		AGATA_SphereTrace::StaticClass());
	TraceTask->OnComplete.AddDynamic(this, &UGameplayAbility_Parry::OnTraceResultCallback);
	TraceTask->SetTraceData(ParryRange, ParryRadius);
	TraceTask->ReadyForActivation();
}

void UGameplayAbility_Parry::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_Parry::OnParry(
	const TScriptInterface<class IAbilitySystemInterface>& TargetASC,
	const FGameplayAbilityTargetDataHandle& TargetDataHandle, int index)
{
	CurrentActorInfo->GetAnimInstance()->Montage_JumpToSection(TEXT("Guard"),
		CurrentActorInfo->GetAnimInstance()->GetCurrentActiveMontage());


	FGameplayAbilitySpecHandle AbilityHandle = TargetASC->GetAbilitySpecHandleByTag(StunTag);
	if (AbilityHandle.IsValid())
	{
		TargetASC->GetAbilitySystemComponent()->TryActivateAbility(AbilityHandle);
	}

	FGameplayEffectSpecHandle EffectHandle =
		MakeOutgoingGameplayEffectSpec(ParryEffect);
	if (EffectHandle.IsValid())
	{
		ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo,
			CurrentActivationInfo, EffectHandle, TargetDataHandle);
	}
}

void UGameplayAbility_Parry::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,
		bReplicatedEndAbility, bWasCancelled);
}

void UGameplayAbility_Parry::InterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,
		bReplicatedEndAbility, bWasCancelled);
}

void UGameplayAbility_Parry::CanceledCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,
		bReplicatedEndAbility, bWasCancelled);
}

void UGameplayAbility_Parry::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& Handle)
{
	for (int i = 0; i < Handle.Num(); i++)
	{
		auto Data = Handle.Data[i];
		AActor* DetectActor = Data->GetHitResult()->GetActor();
		if (!DetectActor)
			continue;

		const TScriptInterface<IAbilitySystemInterface> Interface = DetectActor;
		if (!Interface)
		{
			continue;
		}

		FGameplayAbilitySpecHandle AbilityHandle = Interface->GetAbilitySpecHandleByTag(CheckTag);
		if (!AbilityHandle.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec* Spec =
			Interface->GetAbilitySystemComponent()->FindAbilitySpecFromHandle(AbilityHandle);
		if (!Spec)
		{
			continue;
		}

		if (Spec->IsActive())
		{
			OnParry(Interface, Handle, i);
		}
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
