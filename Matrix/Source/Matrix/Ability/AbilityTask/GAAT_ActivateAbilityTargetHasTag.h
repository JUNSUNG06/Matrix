// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/AbilityTask/AbilityTask_ActivateAbilityByTag.h"
#include "GAAT_ActivateAbilityTargetHasTag.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGAAT_ActivateAbilityTargetHasTag : public UAbilityTask_ActivateAbilityByTag
{
	GENERATED_BODY()
	
public:
	static UGAAT_ActivateAbilityTargetHasTag* CreateTask(UGameplayAbility* OwningAbility,
		AActor* ActivateTarget, FGameplayTag AcrivateTag, 
		AActor* CheckTarget, FGameplayTag CheckTag);

	virtual void Activate() override;


protected:
	AActor* CheckTarget;
	FGameplayTag CheckTag;
};
