// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WidgetType.generated.h"

UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	Game UMETA(DisplayName = "Game"),
	Menu UMETA(DisplayName = "Menu"),
};

UCLASS()
class MATRIX_API AWidgetType : public AActor
{
	GENERATED_BODY()
};
