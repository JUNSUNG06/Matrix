// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTags.h"
#include "GameplayAbilitySpecHandle.h"
#include "AnimNotifyState_ActivateAbility.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UAnimNotifyState_ActivateAbility : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere)
	FGameplayTag ActivateAbilityTag;

private:
	FGameplayAbilitySpecHandle AbilityHandle;
};
