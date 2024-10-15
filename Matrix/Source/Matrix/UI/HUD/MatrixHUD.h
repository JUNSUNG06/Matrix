// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "../../Enum/WidgetType.h"

#include "MatrixHUD.generated.h"

USTRUCT()
struct FWidgetContainer
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<class UMatrixUserWidget*> Array;
};

/**
 * 
 */
UCLASS()
class MATRIX_API AMatrixHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void AddWidget(class UMatrixUserWidget* Widget);

	UFUNCTION(BlueprintCallable)
	void ShowWidget(class UMatrixUserWidget* Widget);
	UFUNCTION(BlueprintCallable)
	void HideWidget(class UMatrixUserWidget* Widget);

protected:
	UPROPERTY()
	TMap<EWidgetType, FWidgetContainer> Widgets;

	class UMatrixUserWidget* ActivateWidget;
};

