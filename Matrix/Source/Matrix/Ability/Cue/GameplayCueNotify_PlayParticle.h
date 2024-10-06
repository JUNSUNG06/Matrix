// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GameplayCueNotify_PlayParticle.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UGameplayCueNotify_PlayParticle : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
	
public:
	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UParticleSystem> Particle;
};
