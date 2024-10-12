// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetDistanceType.generated.h"

UENUM(BlueprintType)
enum class ETargetDistanceType : uint8
{
	Close UMETA(DisplayName = "Close"),
	Middle UMETA(DisplayName = "Middle"),
	Far UMETA(DisplayName = "Far"),
};


UCLASS()
class MATRIX_API ATargetDistanceType : public AActor
{
	GENERATED_BODY()
};
