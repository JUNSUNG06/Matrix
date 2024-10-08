// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_SetAttackWarpTarget.h"
#include "MotionWarpingComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "../../Character/BaseMatrixCharacter.h"

void UAnimNotify_SetAttackWarpTarget::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		ABaseMatrixCharacter* MC = Cast<ABaseMatrixCharacter>(OwnerActor);
		if (MC)
		{
			AActor* TargetActor = MC->Target;
			
			FVector TargetToOwner = (OwnerActor->GetActorLocation() - TargetActor->GetActorLocation()).GetSafeNormal();
			FVector TargetLocation;
			if (FVector::Distance(OwnerActor->GetActorLocation(),
				TargetActor->GetActorLocation()) < (double)Distance)
			{
				TargetLocation = OwnerActor->GetActorLocation();
			}
			else
			{
				TargetLocation = TargetActor->GetActorLocation() + (TargetToOwner * Distance) +
					TargetActor->GetActorRotation().RotateVector(Offset);
			}

			FMotionWarpingTarget Target = {};
			Target.Name = TargetName;
			Target.Location = TargetLocation;
			Target.Rotation = UKismetMathLibrary::FindLookAtRotation(
				OwnerActor->GetActorLocation(), TargetActor->GetActorLocation());
			MC->GetMotionWarping()->AddOrUpdateWarpTarget(Target);
			
			DrawDebugSphere(GetWorld(), TargetLocation, 25.0f, 12, FColor::Green);
		}
	}
}