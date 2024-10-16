// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/MatrixAIController.h"
#include "MatrixEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API AMatrixEnemyController : public AMatrixAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UEnemyWidget> EnemyWidgetClass;

	UPROPERTY()
	class UEnemyWidget* EnemyWidget;
};
