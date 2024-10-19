// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LockOnTarget.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class ULockOnTarget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLockOned);

class MATRIX_API ILockOnTarget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FVector GetLockOnTransform() const;
	virtual FVector GetLockOnTransform_Implementation() const = 0;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AActor* GetLockOnActor();
	virtual AActor* GetLockOnActor_Implementation() = 0;
	UFUNCTION(BlueprintNativeEvent)
	bool CanLockOn();
	virtual bool CanLockOn_Implementation() = 0;
	UFUNCTION(BlueprintNativeEvent)
	void OnLockOned();
	virtual void OnLockOned_Implementation() = 0;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnEndLockOned();
	virtual void OnEndLockOned_Implementation() = 0;
};
