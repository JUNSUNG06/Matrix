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

	void OnParry(class IAbilitySystemInterface* TargetASC);

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

};
