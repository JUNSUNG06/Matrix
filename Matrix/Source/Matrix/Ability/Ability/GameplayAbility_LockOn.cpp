// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_LockOn.h"

#include "../AbilityTask/GAAT_TraceTarget.h"
#include "../TargetActor/GATA_SphereTrace.h"
#include "../../Interface/LockOnTarget.h"
#include "../../Character/BaseMatrixCharacter.h"

UGameplayAbility_LockOn::UGameplayAbility_LockOn()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbility_LockOn::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UGAAT_TraceTarget* TraceTask = UGAAT_TraceTarget::CreateTask(this,
		AGATA_SphereTrace::StaticClass());
	TraceTask->SetTraceData(0.0f, LockOnRadius);
	TraceTask->OnComplete.AddDynamic(this, &UGameplayAbility_LockOn::OnCompleteTrace);
	TraceTask->ReadyForActivation();
}

void UGameplayAbility_LockOn::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

	if (!bIsLockOn)
		return;

	EndLockOn();
}

void UGameplayAbility_LockOn::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	EndLockOn();
}

void UGameplayAbility_LockOn::StartLockOn_Implementation(AActor* TargetActor)
{
	bIsLockOn = true;

	LockOnTargetActor = TargetActor;

	ILockOnTarget::Execute_OnLockOned(TargetActor);
}

void UGameplayAbility_LockOn::EndLockOn_Implementation()
{
	bIsLockOn = false;

	ILockOnTarget::Execute_OnEndLockOned(LockOnTargetActor);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_LockOn::OnCompleteTrace(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	for (int i = 0; i < TargetDataHandle.Data.Num(); i++)
	{
		auto TargetData = TargetDataHandle.Data[i];
		const FHitResult* HitResult = TargetData->GetHitResult();
		if (!HitResult)
			continue;
		AActor* TargetActor = HitResult->GetActor();
		TScriptInterface<ILockOnTarget> LockOnTarget = TargetActor;
		if (!LockOnTarget)
			continue;

		if (ILockOnTarget::Execute_CanLockOn(TargetActor) == false)
			continue;

		StartLockOn(TargetActor);

		return;
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
