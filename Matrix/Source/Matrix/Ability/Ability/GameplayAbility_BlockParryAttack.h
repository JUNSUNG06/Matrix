// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/Ability/GameplayAbility_PlayMontage.h"
#include "GameplayAbility_BlockParryAttack.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_BlockParryAttack : public UGameplayAbility_PlayMontage
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameplayEffect> WarningEffect;
};
