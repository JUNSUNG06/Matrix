// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MatrixAIController.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API AMatrixAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
public:
	void RunAI();
	void StopAI();

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBehaviorTree> BTAsset;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBlackboardData> BBAsset;
};
