// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState/AnimNotifyState_ActivateAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

void UAnimNotifyState_ActivateAbility::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		IAbilitySystemInterface* Interface = Cast<IAbilitySystemInterface>(OwnerActor);
		if (Interface)
		{
			AbilityHandle = Interface->GetAbilitySpecHandleByTag(ActivateAbilityTag);
			if (AbilityHandle.IsValid())
			{
				Interface->GetAbilitySystemComponent()->TryActivateAbility(AbilityHandle);
			}
		}
	}
}

void UAnimNotifyState_ActivateAbility::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		IAbilitySystemInterface* Interface = Cast<IAbilitySystemInterface>(OwnerActor);
		if (Interface)
		{
			if (AbilityHandle.IsValid())
			{
				Interface->GetAbilitySystemComponent()->CancelAbilityHandle(AbilityHandle);
			}
		}
	}
}
