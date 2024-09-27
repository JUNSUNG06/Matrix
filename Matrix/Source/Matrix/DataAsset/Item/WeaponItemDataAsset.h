// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/Item/ItemDataAsset.h"
#include "WeaponItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UWeaponItemDataAsset : public UItemDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Socket, meta = (PrivateAccessAllow = true))
	FTransform EquipSocketOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Socket, meta = (PrivateAccessAllow = true))
	FTransform HoldSocketOffset;

public:
	FORCEINLINE FTransform GetEquipSocketOffset() const { return EquipSocketOffset; }
	FORCEINLINE FTransform GetHoldSocketOffset() const { return HoldSocketOffset; }
};
