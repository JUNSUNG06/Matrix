// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_Teleport.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

void UGameplayAbility_Teleport::OnCompleteQuery(TSharedPtr<FEnvQueryResult> Result)
{
	Super::OnCompleteQuery(Result);
	
	TeleportPoint = Result->GetItemAsLocation(0);

	StartTeleport();

	GetWorld()->GetTimerManager().SetTimer(
		TeleportTimerHandle,
		this,
		&UGameplayAbility_Teleport::CompleteTeleport,
		TeleportTime
	);
}

void UGameplayAbility_Teleport::StartTeleport()
{
	GetAvatarActorFromActorInfo()->CustomTimeDilation = 0.0f;
	GetAvatarActorFromActorInfo()->SetActorHiddenInGame(true);
}

void UGameplayAbility_Teleport::CompleteTeleport()
{
	GetAvatarActorFromActorInfo()->SetActorLocation(TeleportPoint);

	GetAvatarActorFromActorInfo()->CustomTimeDilation = 1.0f;
	GetAvatarActorFromActorInfo()->SetActorHiddenInGame(false);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}