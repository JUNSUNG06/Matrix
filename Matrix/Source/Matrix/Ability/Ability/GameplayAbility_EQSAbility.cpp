// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_EQSAbility.h"
#include "Tasks/AITask_RunEQS.h"
#include "AIController.h"

bool UGameplayAbility_EQSAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
		return false;

	if (!Query)
		return false;

	AAIController* AI = ActorInfo->AvatarActor->GetInstigatorController<AAIController>();
	if (!AI)
		return false;

	return true;
}

void UGameplayAbility_EQSAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AAIController* AI = ActorInfo->AvatarActor->GetInstigatorController<AAIController>();

	UAITask_RunEQS* EQSTask = UAITask_RunEQS::RunEQS(AI, Query);
	FQueryFinishedSignature InNotificationDelegate;
	InNotificationDelegate.BindUObject(this, &UGameplayAbility_EQSAbility::OnComplete);
	EQSTask->SetNotificationDelegate(InNotificationDelegate);
	EQSTask->ReadyForActivation();
}

void UGameplayAbility_EQSAbility::OnComplete(TSharedPtr<FEnvQueryResult> Result)
{
}