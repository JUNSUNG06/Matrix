// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AbilitySystemComponent.h"
#include "BTTask_ActivateAbility.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UBTTask_ActivateAbility : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGameplayTag> AbilityTags;

private:
	FDelegateHandle OnEndAbilityDelegateHandle;
	struct FGameplayAbilitySpecHandle SpecHandle;
	TObjectPtr<UAbilitySystemComponent> CurrentASC;
};
