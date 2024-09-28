// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MCAttributeSetDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UMCAttributeSetDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PrivateAccessAllow = true))
	float MaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PrivateAccessAllow = true))
	float MaxSprintSpeed;

public:
	FORCEINLINE float GetMaxWalkSpeed() { return MaxWalkSpeed; }
	FORCEINLINE float GetMaxSprintSpeed() { return MaxSprintSpeed; }
};
