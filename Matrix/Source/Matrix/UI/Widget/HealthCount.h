// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/MatrixUserWidget.h"
#include "HealthCount.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UHealthCount : public UMatrixUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void Use();
	virtual void Use_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void Reset();
	virtual void Reset_Implementation();
};
