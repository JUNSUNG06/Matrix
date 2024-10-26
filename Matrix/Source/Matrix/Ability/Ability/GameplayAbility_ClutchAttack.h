// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/Ability/GameplayAbility_PlayMontage.h"
#include "GameplayTags.h"
#include "GameplayAbility_ClutchAttack.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_ClutchAttack : public UGameplayAbility_PlayMontage
{
	GENERATED_BODY()
	
public:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
	UPROPERTY(EditAnywhere)
	FGameplayTag StartClutchTag;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> ClutchedAnimMontage;
	UPROPERTY(EditAnywhere)
	float StartClutchAttackDistance;

protected:
	UFUNCTION()
	void TransCamera(bool ReturnToStart);

protected:
	UPROPERTY(EditAnywhere)
	FVector DestCameraSocketOffest;
	UPROPERTY(EditAnywhere)
	FVector DestCameraTargetOffset;
	UPROPERTY(EditAnywhere)
	FRotator DestCameraRotation;

	UPROPERTY(EditAnywhere)
	float TransTime;
	float CurrentTransTime;
	FTimerHandle TransCameraHandle;

	UPROPERTY(EditAnywhere)
	class UCurveFloat* Curve;

	UPROPERTY()
	class APlayerMatrixCharacter* Player;

	UPROPERTY(BlueprintReadOnly)
	AActor* TargetActor;

private:
	FVector StartCameraSocketOffset;
	FVector StartCameraTargetOffset;
	FRotator StartCameraRotation;
};
