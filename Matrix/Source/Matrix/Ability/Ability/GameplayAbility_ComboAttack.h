// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/Ability/GameplayAbility_PlayMontage.h"
#include "GameplayAbility_ComboAttack.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_ComboAttack : public UGameplayAbility_PlayMontage
{
	GENERATED_BODY()

public:
	UGameplayAbility_ComboAttack();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	void StartAttack();
	void SetNextAttack();
	void PlayNextAttack();
	void CheckAttackCombo();
	void SetComboTimer();

protected:
	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = ture))
	int AttackComboCount;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = ture))
	float FrameRate;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = ture))
	TArray<float> ComboCheckFrames;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = ture))
	FString ComboSectionName;

	FTimerHandle ComboCheckTimerHandle;

private:
	int CurrentComboCount;

	bool bIsSetNextCombo;
};
