// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState/ANS_ClutchAttackActionCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Curves/CurveFloat.h"

#include "../../Character/PlayerMatrixCharacter.h"
#include "../../DataAsset/Ability/ClutchAttackDataAsset.h"

void UANS_ClutchAttackActionCamera::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		APlayerMatrixCharacter* Player = Cast<APlayerMatrixCharacter>(OwnerActor);
		if (Player)
		{
			PlayerCameraBoom = Player->GetCameraBoom();
			StartSocketOffset = PlayerCameraBoom->SocketOffset;
			StartSocketOffset = PlayerCameraBoom->TargetOffset;
			StartRotation = PlayerCameraBoom->GetRelativeRotation();

			Duration = TotalDuration;
			CurrentDuration = 0.0f;
		}
	}
}

void UANS_ClutchAttackActionCamera::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!PlayerCameraBoom)
		return;

	CurrentDuration += FrameDeltaTime;

	const float Alpha = Curve->GetFloatValue(CurrentDuration / Duration);

	PlayerCameraBoom->SocketOffset = FMath::Lerp(
		StartSocketOffset,
		Data->GetActionCameraDatas()[Index].GetSocketOffset(),
		Alpha
	);

	PlayerCameraBoom->TargetOffset = FMath::Lerp(
		StartTargetOffset,
		Data->GetActionCameraDatas()[Index].GetTargetOffset(),
		Alpha
	);

	PlayerCameraBoom->SetRelativeRotation(
		FQuat::Slerp(
			StartRotation.Quaternion(),
			Data->GetActionCameraDatas()[Index].GetRotation().Quaternion(), 
			Alpha
		)
	);
}

void UANS_ClutchAttackActionCamera::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	PlayerCameraBoom->SocketOffset =
		Data->GetActionCameraDatas()[Index].GetSocketOffset();

	PlayerCameraBoom->TargetOffset =
		Data->GetActionCameraDatas()[Index].GetTargetOffset();

	PlayerCameraBoom->SetRelativeRotation(
		Data->GetActionCameraDatas()[Index].GetRotation().Quaternion()
	);
}
