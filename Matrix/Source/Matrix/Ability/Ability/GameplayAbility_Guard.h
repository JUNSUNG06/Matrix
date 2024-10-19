// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatrixAbility.h"
#include "GameplayAbility_Guard.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_Guard : public UMatrixAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_Guard();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

public:
	UFUNCTION()
	void OnCompleteCallback();

	UFUNCTION()
	void InterruptedCallback();

	UFUNCTION()
	void CanceledCallback();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> GuardMontage;

	UPROPERTY()
	class UAbilityTask_PlayMontageAndWait* MontageTask;

};
