// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTags.h"
#include "AN_ActivateAbilityWithData.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UAN_ActivateAbilityWithData : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, Meta = (Categories = Event))
	FGameplayTag TargetAbilityTag;
	UPROPERTY(EditAnywhere, Meta = (Categories = Event))
	TObjectPtr<UObject> Object_1;
	UPROPERTY(EditAnywhere, Meta = (Categories = Event))
	TObjectPtr<UObject> Object_2;
	UPROPERTY(EditAnywhere, Meta = (Categories = Event))
	float Magnitude;
};
