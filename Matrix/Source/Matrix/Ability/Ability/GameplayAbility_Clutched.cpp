// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_Clutched.h"

void UGameplayAbility_Clutched::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//const UAnimMontage* ClutchedAnimMontage = Cast<UAnimMontage>(TriggerEventData->OptionalObject);
	//Montage = ClutchedAnimMontage;

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
