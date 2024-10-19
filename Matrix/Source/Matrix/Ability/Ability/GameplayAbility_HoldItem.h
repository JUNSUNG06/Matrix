// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatrixAbility.h"
#include "GameplayAbility_HoldItem.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_HoldItem : public UMatrixAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_HoldItem();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = true))
	int TargetIndex;
};
