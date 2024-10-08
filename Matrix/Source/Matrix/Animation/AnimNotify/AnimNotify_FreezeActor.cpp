// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_FreezeActor.h"

#include "../../MatrixCharacter.h"

void UAnimNotify_FreezeActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp && MeshComp->GetWorld())
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		AMatrixCharacter* MC = Cast<AMatrixCharacter>(OwnerActor);
		MC->Freeze(FreezeTime);
	}
}