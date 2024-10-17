// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/Ability/GameplayAbility_EQSAbility.h"
#include "GameplayAbility_Teleport.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayAbility_Teleport : public UGameplayAbility_EQSAbility
{
	GENERATED_BODY()
	
protected:
	virtual void OnCompleteQuery(TSharedPtr<struct FEnvQueryResult> Result) override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void StartTeleport();
	virtual void StartTeleport_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	void CompleteTeleport();
	virtual void CompleteTeleport_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	void CompleteTeleportDelayed();
	virtual void CompleteTeleportDelayed_Implementation();

protected:
	UPROPERTY(EditAnywhere)
	float TeleportTime;

	UPROPERTY(EditAnywhere)
	float CompleteDelayTime;

	UPROPERTY(EditAnywhere)
	bool bRandom;

	UPROPERTY(BlueprintReadWrite)
	FVector TeleportPoint;
	
	FTimerHandle TeleportTimerHandle;
	FTimerHandle CompleteDelayTimerHandle;
};
