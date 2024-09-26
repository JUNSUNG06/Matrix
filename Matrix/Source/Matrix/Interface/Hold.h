// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "../Enum/HoldType.h"

#include "Hold.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHold : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MATRIX_API IHold
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
public:
	virtual void Hold() = 0;
	virtual void UnHold() = 0;
	virtual AActor* GetHoldActor() = 0;
	virtual EItemHoldType GetHoldType() = 0;
	virtual FTransform GetHoldOffsetTransform() = 0;
};
