// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (PrivateAccessAllow = true))
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (PrivateAccessAllow = true))
	TObjectPtr<class UTexture2D> Image;

public:
	FORCEINLINE FName GetItemName() const { return ItemName; }
	FORCEINLINE TObjectPtr<class UTexture2D> GetImage() const { return Image; }
};
