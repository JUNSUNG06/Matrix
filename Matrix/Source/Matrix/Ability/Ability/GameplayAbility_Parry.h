// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Parry.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_Parry : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnParry(const TScriptInterface<class IAbilitySystemInterface>& TargetASC);
	virtual void OnParry_Implementation(const TScriptInterface<class IAbilitySystemInterface>& TargetASC);

public:
	UFUNCTION()
	void OnCompleteCallback();

	UFUNCTION()
	void InterruptedCallback();

	UFUNCTION()
	void CanceledCallback();

protected:
	UFUNCTION()
	void OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& Handle);

public:
	UPROPERTY(EditAnywhere)
	float ParryRange;
	UPROPERTY(EditAnywhere)
	float ParryRadius;

	UPROPERTY(EditAnywhere)
	FGameplayTag CheckTag;

	UPROPERTY(EditAnywhere)
	FGameplayTag StunTag;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> ParryMontage;

	UPROPERTY()
	class UAbilityTask_PlayMontageAndWait* MontageTask;
};
