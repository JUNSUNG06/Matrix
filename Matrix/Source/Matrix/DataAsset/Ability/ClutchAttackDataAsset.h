// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ClutchAttackDataAsset.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FClutchAttackActionCameraData
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FVector SocketOffest;
	UPROPERTY(EditAnywhere)
	FVector TargetOffset;
	UPROPERTY(EditAnywhere)
	FRotator Rotation;

public:
	FORCEINLINE const FVector GetSocketOffset() { return SocketOffest; }
	FORCEINLINE const FVector GetTargetOffset() { return TargetOffset; }
	FORCEINLINE const FRotator GetRotation() { return Rotation; }
};

UCLASS()
class MATRIX_API UClutchAttackDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	TArray<FClutchAttackActionCameraData> ActionCameraDatas;

public:
	FORCEINLINE TArray<FClutchAttackActionCameraData> GetActionCameraDatas() { return ActionCameraDatas; }
};
