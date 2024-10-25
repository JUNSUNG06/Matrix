// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BGMActor.h"
#include "Components/AudioComponent.h"

// Sets default values
ABGMActor::ABGMActor()
{
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
}

void ABGMActor::Play(USoundBase* Sound, float BlendTime)
{
	Audio->Sound = Sound;
	

	if (BlendTime <= 0.0f)
	{
		Audio->VolumeMultiplier = 1.0f;
		Audio->Play();
		return;
	}

	CurrentBlendTime = 0.0f;
	GetWorld()->GetTimerManager().ClearTimer(PlayBlendTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(StopBlendTimerHandle);
	
	Audio->VolumeMultiplier = 0.0001f;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(
		this,
		&ABGMActor::PlayBlend,
		BlendTime
	);
	GetWorld()->GetTimerManager().SetTimer(
		PlayBlendTimerHandle,
		TimerDelegate,
		GetWorld()->GetDeltaSeconds(),
		true
	);
	Audio->Play();
}

void ABGMActor::Stop(float BlendTime)
{
	if (BlendTime <= 0.0f)
	{
		Audio->Stop();
	}

	CurrentBlendTime = 0.0f;
	GetWorld()->GetTimerManager().ClearTimer(PlayBlendTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(StopBlendTimerHandle);

	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(
		this,
		&ABGMActor::StopBlend,
		BlendTime
	);
	GetWorld()->GetTimerManager().SetTimer(
		StopBlendTimerHandle,
		TimerDelegate,
		GetWorld()->GetDeltaSeconds(),
		true
	);

}

void ABGMActor::PlayBlend(float BlendTime)
{
	CurrentBlendTime += GetWorld()->GetDeltaSeconds();
	if (CurrentBlendTime >= BlendTime)
	{
		Audio->VolumeMultiplier = 1.0f;
		GetWorld()->GetTimerManager().ClearTimer(PlayBlendTimerHandle);

		return;
	}

	float Alpha = CurrentBlendTime / BlendTime;
	Audio->VolumeMultiplier = FMath::Lerp(0.0f, 1.0f, Alpha);
}

void ABGMActor::StopBlend(float BlendTime)
{
	CurrentBlendTime += GetWorld()->GetDeltaSeconds();
	if (CurrentBlendTime >= BlendTime)
	{
		Audio->VolumeMultiplier = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(PlayBlendTimerHandle);
	}

	float Alpha = CurrentBlendTime / BlendTime;
	Audio->VolumeMultiplier = FMath::Lerp(1.0f, 0.0f, Alpha);
}