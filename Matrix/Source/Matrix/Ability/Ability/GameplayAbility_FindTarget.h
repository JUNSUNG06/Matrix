// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatrixAbility.h"
#include "GameplayAbility_FindTarget.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_FindTarget : public UMatrixAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_FindTarget();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void Find(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	UFUNCTION()
	virtual void Find_Implementation(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

public:
	UPROPERTY(EditAnywhere)
	float FindRange;
	UPROPERTY(EditAnywhere)
	float FindRadius;
};
