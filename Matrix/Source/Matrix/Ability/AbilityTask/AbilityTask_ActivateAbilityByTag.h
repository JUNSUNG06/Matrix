// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GameplayTags.h"
#include "AbilityTask_ActivateAbilityByTag.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UAbilityTask_ActivateAbilityByTag : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "AbilityTasks", meta = (DisplayName =
		"WaitForTrace", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility",
		BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_ActivateAbilityByTag* CreateTask(UGameplayAbility* OwningAbility,
		AActor* ActivateTarget, FGameplayTag ActivateTag);

	virtual void Activate() override;


protected:
	AActor* ActivateTarget;
	FGameplayTag ActivateTag;
};
