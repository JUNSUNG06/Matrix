// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ActorWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UActorWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	virtual void SetOwnerActor(AActor* NewOwnerActor);

protected:
	TObjectPtr<AActor> OwnerActor;
};
