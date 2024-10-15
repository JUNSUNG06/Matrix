// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/MatrixUserWidget.h"
#include "ActorUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UActorUserWidget : public UMatrixUserWidget
{
	GENERATED_BODY()

protected:
	TObjectPtr<AActor> OwnerActor;

public:
	UFUNCTION(BlueprintCallable)
	virtual void SetOwnerActor(AActor* NewOwnerActor);

	FORCEINLINE const AActor* GetOwnerActor() { return OwnerActor; }
};
