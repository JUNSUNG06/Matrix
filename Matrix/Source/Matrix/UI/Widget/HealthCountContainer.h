// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/MatrixUserWidget.h"
#include "HealthCountContainer.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UHealthCountContainer : public UMatrixUserWidget
{
	GENERATED_BODY()

public:
	UHealthCountContainer();
	
public:
	void SetHealthCount(int Count);
	void Use();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UHealthCount> HealthCountClass;

	TArray<class UHealthCount*> HealthCounts;

	int CurrentIndex;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UHorizontalBox* HB_CountContainer;
};
