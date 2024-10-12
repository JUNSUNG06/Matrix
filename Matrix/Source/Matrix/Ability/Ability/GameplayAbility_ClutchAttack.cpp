// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_ClutchAttack.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "../../Character/BaseMatrixCharacter.h"

bool UGameplayAbility_ClutchAttack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
		return false;

	ABaseMatrixCharacter* BMC = Cast<ABaseMatrixCharacter>(ActorInfo->AvatarActor);
	if (!BMC)
		return false;
	if (!BMC->Target)
		return false;

	return true;
}

void UGameplayAbility_ClutchAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ABaseMatrixCharacter* BMC = Cast<ABaseMatrixCharacter>(ActorInfo->AvatarActor);
	AActor* TargetActor = BMC->Target;
	TScriptInterface<IAbilitySystemInterface> TargetASI = TargetActor;

	FGameplayEventData Payload;
	Payload.Instigator = GetAvatarActorFromActorInfo();
	Payload.OptionalObject = ClutchedAnimMontage;
	auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	TargetASI->GetAbilitySystemComponent()->TriggerAbilityFromGameplayEvent(
		TargetASI->GetAbilitySpecHandleByTag(StartClutchTag),
		TargetASI->GetAbilitySystemComponent()->AbilityActorInfo.Get(),
		StartClutchTag,
		&Payload,
		*TargetASC);

	FVector AttackLocation = TargetActor->GetActorLocation() +
		TargetActor->GetActorForwardVector() * StartClutchAttackDistance;
	GetAvatarActorFromActorInfo()->SetActorLocation(AttackLocation);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}