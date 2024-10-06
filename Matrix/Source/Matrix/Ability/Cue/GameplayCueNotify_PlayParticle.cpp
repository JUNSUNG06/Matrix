// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Cue/GameplayCueNotify_PlayParticle.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Particles/ParticleSystemComponent.h"

bool UGameplayCueNotify_PlayParticle::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	AActor* Actor = UAbilitySystemBlueprintLibrary::GetInstigatorActor(Parameters);
	UParticleSystemComponent* PS = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, Actor->GetActorLocation());
	PS->bAutoDestroy = true;

	return true;
}
