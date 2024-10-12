// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AN_ActivateAbilityWithData.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAN_ActivateAbilityWithData::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		
		FGameplayEventData Payload = {};
		Payload.OptionalObject = Object_1;
		Payload.OptionalObject2 = Object_2;
		Payload.EventMagnitude = Magnitude;

		TScriptInterface<IAbilitySystemInterface> ASI = OwnerActor;
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerActor);
		ASC->TriggerAbilityFromGameplayEvent(
			ASI->GetAbilitySpecHandleByTag(TargetAbilityTag),
			ASI->GetAbilitySystemComponent()->AbilityActorInfo.Get(),
			TargetAbilityTag,
			&Payload,
			*ASC);
	}
}
