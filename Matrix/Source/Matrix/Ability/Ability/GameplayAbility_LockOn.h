// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_LockOn.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_LockOn : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_LockOn();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void SetTarget(const TScriptInterface<class ILockOnTarget>& LockOnTarget);
	virtual void SetTarget_Implementation(const TScriptInterface<class ILockOnTarget>& LockOnTarget);

	UFUNCTION(BlueprintNativeEvent)
	void OnEndLockOn();
	virtual void OnEndLockOn_Implementation();

public:
	UPROPERTY(EditAnywhere)
	float  LockOnRadius;

private:
	UFUNCTION()
	void OnCompleteTrace(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

private:
	bool bIsLockOn;
};
