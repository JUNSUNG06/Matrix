// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MatrixPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API AMatrixPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMatrixUserWidget> PlayerWidgetClass;

	UPROPERTY()
	class UMatrixUserWidget* PlayerWidget;
};
