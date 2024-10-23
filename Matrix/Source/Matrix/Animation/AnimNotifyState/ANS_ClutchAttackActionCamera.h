// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_ClutchAttackActionCamera.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UANS_ClutchAttackActionCamera : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere)
	int Index;

	UPROPERTY(EditAnywhere)
	class UClutchAttackDataAsset* Data;

	UPROPERTY(EditAnywhere)
	class UCurveFloat* Curve;

protected:
	class USpringArmComponent* PlayerCameraBoom;

protected:
	float Duration;
	float CurrentDuration;

	FVector StartSocketOffset;
	FVector StartTargetOffset;
	FRotator StartRotation;
};