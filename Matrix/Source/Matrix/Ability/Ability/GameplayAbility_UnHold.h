// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_UnHold.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_UnHold : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_UnHold();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

};
