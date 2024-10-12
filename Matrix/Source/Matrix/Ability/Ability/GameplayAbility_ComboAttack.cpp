// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_ComboAttack.h"

UGameplayAbility_ComboAttack::UGameplayAbility_ComboAttack()
{
	CurrentComboCount = 0;
}

void UGameplayAbility_ComboAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	StartAttack();
}

void UGameplayAbility_ComboAttack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ComboCheckTimerHandle.IsValid())
	{
		SetNextAttack();
	}
}

void UGameplayAbility_ComboAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	CurrentComboCount = 0;
	bIsSetNextCombo = false;
	ComboCheckTimerHandle.Invalidate();
}

void UGameplayAbility_ComboAttack::StartAttack()
{
	SetComboTimer();
}

void UGameplayAbility_ComboAttack::SetNextAttack()
{
	bIsSetNextCombo = true;

	if (!ComboCheckTimerHandle.IsValid())
		PlayNextAttack();
}

void UGameplayAbility_ComboAttack::PlayNextAttack()
{
	bIsSetNextCombo = false;

	CurrentComboCount++;
	SetComboTimer();

	FName SectionName = *FString::Printf(TEXT("%s_%d"), *ComboSectionName, CurrentComboCount);
	MontageJumpToSection(SectionName);
}

void UGameplayAbility_ComboAttack::CheckAttackCombo()
{
	if (bIsSetNextCombo)
	{
		PlayNextAttack();
	}
}

void UGameplayAbility_ComboAttack::SetComboTimer()
{
	ComboCheckTimerHandle.Invalidate();

	if (!ComboCheckFrames.IsValidIndex(CurrentComboCount))
		return;

	float NextComboCheckTime = ComboCheckFrames[CurrentComboCount] /
		FrameRate;
	UE_LOG(LogTemp, Log, TEXT("%f"), NextComboCheckTime);
	if (NextComboCheckTime <= 0.0f)
		return;

	GetWorld()->GetTimerManager().SetTimer(ComboCheckTimerHandle, this, 
		&UGameplayAbility_ComboAttack::CheckAttackCombo, NextComboCheckTime, false);
}
