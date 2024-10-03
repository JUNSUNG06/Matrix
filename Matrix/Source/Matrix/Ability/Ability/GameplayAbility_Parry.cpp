// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_Parry.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

#include "../AbilityTask/GAAT_TraceTarget.h"
#include "../TargetActor/GATA_SphereTrace.h"

void UGameplayAbility_Parry::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	UE_LOG(LogTemp, Log, TEXT("Try Parry"));

	UGAAT_TraceTarget* TraceTask = UGAAT_TraceTarget::CreateTask(this,
		AGATA_SphereTrace::StaticClass());
	TraceTask->OnComplete.AddDynamic(this, &UGameplayAbility_Parry::OnTraceResultCallback);
	TraceTask->SetTraceData(ParryRange, ParryRadius);
	TraceTask->ReadyForActivation();
}

void UGameplayAbility_Parry::OnParry(IAbilitySystemInterface* TargetASC)
{
	FGameplayAbilitySpecHandle Handle = TargetASC->GetAbilitySpecHandleByTag(StunTag);
	if (Handle.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Parry"));

		TargetASC->GetAbilitySystemComponent()->TryActivateAbility(Handle);
	}
}

void UGameplayAbility_Parry::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& Handle)
{
	UE_LOG(LogTemp, Log, TEXT("%d"), Handle.Num());

	for (int i = 0; i < Handle.Num(); i++)
	{
		auto Data = Handle.Data[i];
		AActor* DetectActor = Data->GetHitResult()->GetActor();
		if (!DetectActor)
			continue;
		UE_LOG(LogTemp, Log, TEXT("%s"), *DetectActor->GetName());
		IAbilitySystemInterface* Interface = Cast<IAbilitySystemInterface>(DetectActor);
		if (!Interface)
		{
			continue;
		}
		UE_LOG(LogTemp, Log, TEXT("1"));

		FGameplayAbilitySpecHandle Handle = Interface->GetAbilitySpecHandleByTag(CheckTag);
		if (!Handle.IsValid())
		{
			continue;
		}
		UE_LOG(LogTemp, Log, TEXT("2"));

		FGameplayAbilitySpec* Spec =
			Interface->GetAbilitySystemComponent()->FindAbilitySpecFromHandle(Handle);
		if (!Spec)
		{
			continue;
		}
		UE_LOG(LogTemp, Log, TEXT("3"));

		if (Spec->IsActive())
		{
			OnParry(Interface);
		}
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
