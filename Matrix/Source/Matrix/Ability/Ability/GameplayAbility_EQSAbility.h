// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatrixAbility.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameplayAbility_EQSAbility.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_EQSAbility : public UMatrixAbility
{
	GENERATED_BODY()

public:
	UGameplayAbility_EQSAbility();

public:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UEnvQuery> Query;

protected:
	virtual void OnCompleteQuery(TSharedPtr<FEnvQueryResult> Result);
};
