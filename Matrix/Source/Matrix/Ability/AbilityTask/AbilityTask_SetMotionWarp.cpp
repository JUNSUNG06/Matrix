// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityTask/AbilityTask_SetMotionWarp.h"

UAbilityTask_SetMotionWarp* UAbilityTask_SetMotionWarp::CreateTask(UGameplayAbility* OwningAbility, FName TargetName, FVector Location, FRotator Rotation)
{
	UAbilityTask_SetMotionWarp* NewTask = NewAbilityTask<UAbilityTask_SetMotionWarp>(OwningAbility);
	
	NewTask->WarpTarget = {};
	NewTask->WarpTarget.Name = TargetName;
	NewTask->WarpTarget.Location = Location;
	NewTask->WarpTarget.Rotation = Rotation;
	
	return NewTask;
}

void UAbilityTask_SetMotionWarp::Activate()
{
	Super::Activate();

	AActor* Actor = Ability->GetAvatarActorFromActorInfo();
	UMotionWarpingComponent* MW = Actor->GetComponentByClass<UMotionWarpingComponent>();
	if (MW)
	{
		MW->AddOrUpdateWarpTarget(WarpTarget);
		
		DrawDebugSphere(GetWorld(), WarpTarget.Location, 25.0f, 12, FColor::Green);
	}

	EndTask();
}
