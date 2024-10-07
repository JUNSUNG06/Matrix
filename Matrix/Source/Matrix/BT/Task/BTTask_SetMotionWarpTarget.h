// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetMotionWarpTarget.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UBTTask_SetMotionWarpTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

public:
	UPROPERTY(EditAnywhere)
	FVector Offset;
	UPROPERTY(EditAnywhere)
	FName TargetName;
};
