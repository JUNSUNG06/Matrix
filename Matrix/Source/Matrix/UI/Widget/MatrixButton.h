// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "MatrixButton.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UMatrixButton : public UButton
{
	GENERATED_BODY()

public:
	UMatrixButton();

protected:
	UFUNCTION()
	void OnHover();
	UFUNCTION()
	void OnUnhover();
	UFUNCTION()
	void OnClick();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor OnHoverColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor DefaultColor;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* OnHoverSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* OnClickSound;
};
