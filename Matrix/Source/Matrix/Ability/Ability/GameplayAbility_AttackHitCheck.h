// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_AttackHitCheck.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_AttackHitCheck : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_AttackHitCheck();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UFUNCTION()
	void OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

protected:
	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<class UGameplayEffect> AttackDamageEffect;

protected:
	UPROPERTY(EditAnywhere, Category = "Trace")
	float TraceRange;
	UPROPERTY(EditAnywhere, Category = "Trace")
	float TraceRadius;
};
