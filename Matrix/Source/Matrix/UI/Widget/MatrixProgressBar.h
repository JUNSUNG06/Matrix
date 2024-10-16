// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/MatrixUserWidget.h"
#include "MatrixProgressBar.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UMatrixProgressBar : public UMatrixUserWidget
{
	GENERATED_BODY()

public:
	void SetPercent(float Value, bool Immediately = false);
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* PB_Bottom;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* PB_Top;

protected:
	void Follow();

protected:
	UPROPERTY(EditAnywhere)
	float FollowTime;
	FTimerHandle FollowTimerHandle;
};
