// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/MatrixUserWidget.h"
#include "TwoSideProgressBar.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UTwoSideProgressBar : public UMatrixUserWidget
{
	GENERATED_BODY()
	
public:
	void SetPercent(float Value);
	float GetPercent();

protected:
	UPROPERTY(EditAnywhere)
	float Percent;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* PB_Left;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* PB_Right;
};
