// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemHoldType.generated.h"

UENUM(BlueprintType)
enum class EItemHoldType : uint8
{
	UnHold UMETA(DisplayName = "UnHold"),
	Sword UMETA(DisplayName = "Sword"),
	LongSword UMETA(DisplayName = "LongSword"),
};

UCLASS()
class MATRIX_API AItemHoldType : public AActor
{
	GENERATED_BODY()
};
