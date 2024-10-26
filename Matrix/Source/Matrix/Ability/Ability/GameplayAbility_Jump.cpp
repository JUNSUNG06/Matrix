// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_Jump.h"
#include "GameFramework/Character.h"
#include "../../Character/BaseMatrixCharacter.h"

bool UGameplayAbility_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if(!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
		return false;

	ABaseMatrixCharacter* MC = Cast<ABaseMatrixCharacter>(ActorInfo->AvatarActor);
	if (!MC->CanJump())
		return false;

	return true;
}

void UGameplayAbility_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	OwnerMC->Jump();
	OwnerMC->LandedDelegate.AddDynamic(this, &UGameplayAbility_Jump::OnLand);
}

void UGameplayAbility_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	OwnerMC->LandedDelegate.RemoveDynamic(this, &UGameplayAbility_Jump::OnLand);
	OwnerMC->StopJumping();
}

void UGameplayAbility_Jump::OnLand(const FHitResult& Hit)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
