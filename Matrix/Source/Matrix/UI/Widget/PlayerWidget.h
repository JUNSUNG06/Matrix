// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/ActorUserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UPlayerWidget : public UActorUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetOwnerActor(AActor* NewOwnerActor) override;

	void SetHealthPercent(float Value, bool Immediately = false);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UMatrixProgressBar* PB_Health;

protected:
	UFUNCTION()
	void OnHealthChange(float Prev, float New, float Max);
};
