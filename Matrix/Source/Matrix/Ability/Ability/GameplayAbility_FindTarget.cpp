// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_FindTarget.h"

#include "../AbilityTask/GAAT_TraceTarget.h"
#include "../TargetActor/GATA_SphereTrace.h"
#include "../../Character/BaseMatrixCharacter.h"

UGameplayAbility_FindTarget::UGameplayAbility_FindTarget()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbility_FindTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	UGAAT_TraceTarget* TraceTask = UGAAT_TraceTarget::CreateTask(this, AGATA_SphereTrace::StaticClass());
	TraceTask->OnComplete.AddDynamic(this, &UGameplayAbility_FindTarget::Find_Implementation);
	TraceTask->SetTraceData(FindRange, FindRadius);
	TraceTask->ReadyForActivation();
}

void UGameplayAbility_FindTarget::Find_Implementation(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	Find(TargetDataHandle);
}
