// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BGMActor.generated.h"

UCLASS()
class MATRIX_API ABGMActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABGMActor();

public:
	UFUNCTION(BlueprintCallable)
	void Play(class USoundBase* Sound, float BlendTime);
	UFUNCTION(BlueprintCallable)
	void Stop(float BlendTime);

protected:
	UFUNCTION()
	void PlayBlend(float BlendTime);
	UFUNCTION()
	void StopBlend(float BlendTime);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UAudioComponent> Audio;


protected:
	FTimerHandle PlayBlendTimerHandle;
	FTimerHandle StopBlendTimerHandle;

	float CurrentBlendTime;
};
