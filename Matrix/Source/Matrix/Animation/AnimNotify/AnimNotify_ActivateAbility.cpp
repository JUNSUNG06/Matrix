// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_ActivateAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

void UAnimNotify_ActivateAbility::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		IAbilitySystemInterface* Interface = Cast<IAbilitySystemInterface>(OwnerActor);
		if (Interface)
		{
			FGameplayAbilitySpecHandle Handle =
				Interface->GetAbilitySpecHandleByTag(TargetAbilityTag);
			if (Handle.IsValid())
			{
				Interface->GetAbilitySystemComponent()->TryActivateAbility(Handle);
			}
		}
	}
	
	//MotionWarp AnimNortify ±¸Çö
}
