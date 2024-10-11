// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyStateType.generated.h"

UENUM(BlueprintType)
enum class EEnemyStateType : uint8
{
	Attack UMETA(DisplayName = "Attack"),
	Move UMETA(DisplayName = "Move"),
	Stun UMETA(DisplayName = "Stun"),
	Clutched UMETA(DisplayName = "Clutched"),
};

UCLASS()
class MATRIX_API AEnemyStateType : public AActor
{
	GENERATED_BODY()
};
