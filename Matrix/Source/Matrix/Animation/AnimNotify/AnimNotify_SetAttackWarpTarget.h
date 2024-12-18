// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SetAttackWarpTarget.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UAnimNotify_SetAttackWarpTarget : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere)
	FName TargetName;
	UPROPERTY(EditAnywhere)
	float MaxDistance;
	UPROPERTY(EditAnywhere)
	FVector Offset;
};
