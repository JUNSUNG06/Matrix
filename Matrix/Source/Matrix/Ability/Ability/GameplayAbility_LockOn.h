// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatrixAbility.h"
#include "GameplayAbility_LockOn.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_LockOn : public UMatrixAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_LockOn();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void StartLockOn(AActor* TargetActor);
	virtual void StartLockOn_Implementation(AActor* TargetActor);

	UFUNCTION(BlueprintNativeEvent)
	void EndLockOn();
	virtual void EndLockOn_Implementation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float  LockOnRadius;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> LockOnTargetActor;

private:
	UFUNCTION()
	void OnCompleteTrace(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

private:
	bool bIsLockOn;
};
