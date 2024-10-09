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

	OnEndLockOn();
}

void UGameplayAbility_LockOn::SetTarget_Implementation(const TScriptInterface<class ILockOnTarget>& LockOnTarget)
{
	bIsLockOn = true;

	SetTarget(LockOnTarget);
}

void UGameplayAbility_LockOn::OnEndLockOn_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("end lockon"));

	bIsLockOn = false;

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

		if (LockOnTarget->CanLockOn_Implementation() == false)
			continue;

		UE_LOG(LogTemp, Log, TEXT("find lockon target"));
		SetTarget_Implementation(LockOnTarget);
		
		break;
	}
}
