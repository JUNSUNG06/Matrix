// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_ClutchAttack.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Curves/CurveFloat.h"

#include "../../Character/BaseMatrixCharacter.h"
#include "../../Character/PlayerMatrixCharacter.h"

bool UGameplayAbility_ClutchAttack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
		return false;

	ABaseMatrixCharacter* BMC = Cast<ABaseMatrixCharacter>(ActorInfo->AvatarActor);
	if (!BMC)
		return false;
	if (!BMC->GetTarget())
		return false;
	TScriptInterface<IAbilitySystemInterface> TargetASI = BMC->GetTarget();
	if (!TargetASI)
		return false;

	return true;
}

void UGameplayAbility_ClutchAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ABaseMatrixCharacter* BMC = Cast<ABaseMatrixCharacter>(ActorInfo->AvatarActor);
	TargetActor = BMC->GetTarget();
	TScriptInterface<IAbilitySystemInterface> TargetASI = TargetActor;

	FGameplayEventData Payload;
	Payload.Instigator = GetAvatarActorFromActorInfo();
	Payload.OptionalObject = ClutchedAnimMontage;
	auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	TargetASI->GetAbilitySystemComponent()->TriggerAbilityFromGameplayEvent(
		TargetASI->GetAbilitySpecHandleByTag(StartClutchTag),
		TargetASI ->GetAbilitySystemComponent()->AbilityActorInfo.Get(),
		StartClutchTag,
		&Payload,
		*TargetASC);

	FVector AttackLocation = TargetActor->GetActorLocation() +
		TargetActor->GetActorForwardVector() * StartClutchAttackDistance;
	GetAvatarActorFromActorInfo()->SetActorLocation(AttackLocation);

	FRotator AttackRotation = UKismetMathLibrary::FindLookAtRotation(
		GetAvatarActorFromActorInfo()->GetActorLocation(),
		TargetActor->GetActorLocation()
	);
	GetAvatarActorFromActorInfo()->SetActorRotation(AttackRotation);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Player = Cast<APlayerMatrixCharacter>(GetAvatarActorFromActorInfo());
	if (Player)
	{
		Player->DisableInput(GetWorld()->GetFirstPlayerController());

		StartCameraSocketOffset = Player->GetCameraBoom()->SocketOffset;
		StartCameraTargetOffset = Player->GetCameraBoom()->TargetOffset;
		StartCameraRotation = Player->GetController()->GetControlRotation();

		CurrentTransTime = 0.0f;

		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(
			this,
			&UGameplayAbility_ClutchAttack::TransCamera,
			false
		);
		GetWorld()->GetTimerManager().SetTimer(
			TransCameraHandle,
			TimerDelegate,
			GetWorld()->GetDeltaSeconds(),
			true
		);
	}
}

void UGameplayAbility_ClutchAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (Player)
	{
		CurrentTransTime = 0.0f;
		
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(
			this,
			&UGameplayAbility_ClutchAttack::TransCamera,
			true
		);
		GetWorld()->GetTimerManager().SetTimer(
			TransCameraHandle,
			TimerDelegate,
			GetWorld()->GetDeltaSeconds(),
			true
		);

		Player->EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void UGameplayAbility_ClutchAttack::TransCamera(bool ReturnToStart)
{
	CurrentTransTime += GetWorld()->GetDeltaSeconds();
	float Alpha = Curve ? Curve->GetFloatValue(CurrentTransTime / TransTime) : CurrentTransTime / TransTime;

	const FVector& SocketStart = ReturnToStart ? DestCameraSocketOffest : StartCameraSocketOffset;
	const FVector& SocketDest = ReturnToStart ? StartCameraSocketOffset : DestCameraSocketOffest;
	const FVector& TargetStart = ReturnToStart ? DestCameraTargetOffset : StartCameraTargetOffset;
	const FVector& TargetDest = ReturnToStart ? StartCameraTargetOffset : DestCameraTargetOffset;
	const FRotator& RotationStart = ReturnToStart ? 
		DestCameraRotation + FRotator(0.0f, StartCameraRotation.Yaw, 0.0f) : StartCameraRotation;
	const FRotator& RotationDest = ReturnToStart ? StartCameraRotation : 
		DestCameraRotation + FRotator(0.0f, StartCameraRotation.Yaw, 0.0f);
	
	if (Alpha >= 1.0f)
	{
		Player->GetCameraBoom()->SocketOffset = SocketDest;
		Player->GetCameraBoom()->TargetOffset = TargetDest;
		Player->GetController()->SetControlRotation(RotationDest);

		GetWorld()->GetTimerManager().ClearTimer(TransCameraHandle);

		return;
	}
	else
	{
		Player->GetCameraBoom()->SocketOffset = FMath::Lerp(SocketStart, SocketDest, Alpha);
		Player->GetCameraBoom()->TargetOffset = FMath::Lerp(TargetStart, TargetDest, Alpha);
		Player->GetController()->SetControlRotation(FQuat::Slerp(RotationStart.Quaternion(), RotationDest.Quaternion(), Alpha).Rotator());
	}
}
