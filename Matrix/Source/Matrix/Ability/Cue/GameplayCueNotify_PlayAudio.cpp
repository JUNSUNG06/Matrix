// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Cue/GameplayCueNotify_PlayAudio.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"

bool UGameplayCueNotify_PlayAudio::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	AActor* Actor = UAbilitySystemBlueprintLibrary::GetInstigatorActor(Parameters);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Actor->GetActorLocation());

	return true;
}
