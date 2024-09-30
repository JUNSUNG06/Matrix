// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_Interact.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "../AbilityTask/GAAT_TraceTarget.h"
#include "../TargetActor/GATA_SphereTrace.h"
#include "../../Interface/Interact.h"

UGameplayAbility_Interact::UGameplayAbility_Interact()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbility_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UE_LOG(LogTemp, Log, TEXT("Interact"));

	UGAAT_TraceTarget* TraceTarget = UGAAT_TraceTarget::CreateTask(this, AGATA_SphereTrace::StaticClass());
	TraceTarget->OnComplete.AddDynamic(this, &UGameplayAbility_Interact::OnTraceResultCallback);
	TraceTarget->SetTraceData(DetectRange, DetectRadius);
	TraceTarget->ReadyForActivation();
}

void UGameplayAbility_Interact::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& Handle)
{
	for (int i = 0; i < Handle.Num(); i++)
	{
		auto Data = Handle.Data[i];
		AActor* DetectActor = Data->GetHitResult()->GetActor();
		IInteract* Interact = Cast<IInteract>(DetectActor);
		if (Interact)
		{
			UE_LOG(LogTemp, Log, TEXT("Interact Detect : %s"), *DetectActor->GetName());
			Interact->Interact(CurrentActorInfo->AvatarActor.Get());

			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);

			return;
		}
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
