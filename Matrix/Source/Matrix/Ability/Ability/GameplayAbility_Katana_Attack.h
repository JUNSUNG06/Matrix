// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTags.h"
#include "GameplayAbility_Katana_Attack.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_Katana_Attack : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_Katana_Attack();

public:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

public:
	UPROPERTY(EditAnywhere)
	float CheckEnemyRange;
	UPROPERTY(EditAnywhere)
	float CheckEnemyRadius;

private:
	UFUNCTION()
	void CompleteTraceTask(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

public:
	UPROPERTY(EditAnywhere)
	FGameplayTag ComboAttackTag;

	UPROPERTY(EditAnywhere)
	FGameplayTag StunTag;
	UPROPERTY(EditAnywhere)
	FGameplayTag StunClutchAttackTag;
};
