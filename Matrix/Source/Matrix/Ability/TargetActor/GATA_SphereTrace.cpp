// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/TargetActor/GATA_SphereTrace.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"

AGATA_SphereTrace::AGATA_SphereTrace() : 
	TraceRange(0.0f),
	TraceRadius(0.0f)
{
	
}

void AGATA_SphereTrace::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

void AGATA_SphereTrace::ConfirmTargetingAndContinue()
{
	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle DataHandle = MakeTargetData();
		TargetDataReadyDelegate.Broadcast(DataHandle);
	}
}

void AGATA_SphereTrace::SetTraceData(float Range, float Radius)
{
	TraceRange = Range;
	TraceRadius = Radius;
}

FGameplayAbilityTargetDataHandle AGATA_SphereTrace::MakeTargetData() const
{
	TArray<FHitResult> HitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(AGATA_SphereTrace), false, SourceActor);
	FVector Start = SourceActor->GetActorForwardVector() * TraceRange + SourceActor->GetActorLocation();

	bool HitDetected = GetWorld()->SweepMultiByChannel(HitResult, Start, Start, FQuat::Identity,
		ECC_Visibility, FCollisionShape::MakeSphere(TraceRadius), Params);
	
	FGameplayAbilityTargetDataHandle DataHandle;
	if (HitDetected)
	{
		for (FHitResult const Hit : HitResult)
		{
			FGameplayAbilityTargetData_SingleTargetHit* TargetData =
				new FGameplayAbilityTargetData_SingleTargetHit(Hit);
			DataHandle.Add(TargetData);
		}
	}

#if ENABLE_DRAW_DEBUG
	if (bShowDebug)
	{
		FVector SphereOrigin = Start;
		FColor Color = HitDetected ? FColor::Green : FColor::Red;
		DrawDebugSphere(GetWorld(), Start, TraceRadius, 32, Color, false, 3.0f);
	}
#endif

	return DataHandle;
}
