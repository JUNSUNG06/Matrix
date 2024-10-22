// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameCycle.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UGameCycle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameClear);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameFail);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePause, bool, IsPause);

class MATRIX_API IGameCycle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Clear();
	virtual void Clear_Implementation() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Fail();
	virtual void Fail_Implementation() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Pause(bool IsPause);
	virtual void Pause_Implementation(bool IsPause) = 0;
};
