// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Enum/WidgetType.h"
#include "MatrixUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UMatrixUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	EWidgetType WidgetType;

public:
	FORCEINLINE EWidgetType GetWidgetType() { return WidgetType; }
};
