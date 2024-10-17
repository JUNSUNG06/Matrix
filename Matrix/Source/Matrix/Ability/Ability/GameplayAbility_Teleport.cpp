// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_Teleport.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

void UGameplayAbility_Teleport::OnCompleteQuery(TSharedPtr<FEnvQueryResult> Result)
{
	Super::OnCompleteQuery(Result);
	
	TArray<FVector> ResultPoint;
	Result->GetAllAsLocations(ResultPoint);

	if (bRandom)
	{
		TeleportPoint = Result->GetItemAsLocation(FMath::RandRange(0, ResultPoint.Num() - 1));

	}
	else
	{
		TeleportPoint = ResultPoint[0];
	}

	StartTeleport();

	GetWorld()->GetTimerManager().SetTimer(
		TeleportTimerHandle,
		this,
		&UGameplayAbility_Teleport::CompleteTeleport,
		TeleportTime
	);
}

void UGameplayAbility_Teleport::StartTeleport_Implementation()
{
	GetAvatarActorFromActorInfo()->CustomTimeDilation = 0.0f;
	GetAvatarActorFromActorInfo()->SetActorHiddenInGame(true);
}

void UGameplayAbility_Teleport::CompleteTeleport_Implementation()
{
	GetAvatarActorFromActorInfo()->SetActorLocation(TeleportPoint);

	GetWorld()->GetTimerManager().SetTimer(
		CompleteDelayTimerHandle,
		this,
		&UGameplayAbility_Teleport::CompleteTeleportDelayed,
		CompleteDelayTime
	);
}

void UGameplayAbility_Teleport::CompleteTeleportDelayed_Implementation()
{
	GetAvatarActorFromActorInfo()->CustomTimeDilation = 1.0f;
	GetAvatarActorFromActorInfo()->SetActorHiddenInGame(false);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
