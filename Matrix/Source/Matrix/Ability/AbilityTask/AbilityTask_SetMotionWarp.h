// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MotionWarpingComponent.h"

#include "AbilityTask_SetMotionWarp.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UAbilityTask_SetMotionWarp : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	static UAbilityTask_SetMotionWarp* CreateTask(UGameplayAbility* OwningAbility,
		FName TargetName, FVector TargetLocation, FRotator TargetRotation = FRotator::ZeroRotator);

public:
	virtual void Activate() override;

private:
	FMotionWarpingTarget WarpTarget;
};
