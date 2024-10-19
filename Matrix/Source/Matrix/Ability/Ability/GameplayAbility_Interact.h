// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatrixAbility.h"
#include "GameplayAbility_Interact.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_Interact : public UMatrixAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_Interact();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UFUNCTION()
	void OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& Handle);

public:
	UPROPERTY(EditAnywhere)
	float DetectRange;

	UPROPERTY(EditAnywhere)
	float DetectRadius;
};
