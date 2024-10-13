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
	virtual void StartTeleport();
	virtual void CompleteTeleport();

protected:
	UPROPERTY(EditAnywhere)
	float TeleportTime;

	FTimerHandle TeleportTimerHandle;

	FVector TeleportPoint;
};
