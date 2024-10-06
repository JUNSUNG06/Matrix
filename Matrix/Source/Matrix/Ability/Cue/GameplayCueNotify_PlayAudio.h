// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GameplayCueNotify_PlayAudio.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayCueNotify_PlayAudio : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
	
public:
	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundBase> Sound;
};
