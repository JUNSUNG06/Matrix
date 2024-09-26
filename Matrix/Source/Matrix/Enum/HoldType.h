// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HoldType.generated.h"

UENUM(BlueprintType)
enum class EItemHoldType : uint8
{
	UnHold UMETA(UnHold = "Option A"),
	Sword UMETA(Sword = "Option A"),
};

UCLASS()
class MATRIX_API AHoldType : public AActor
{
	GENERATED_BODY()
};
