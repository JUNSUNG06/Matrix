// Fill out your copyright notice in the Description page of Project Settings.


#include "BT/Task/BTTask_ActivateAbility.h"
#include "AbilitySystemInterface.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = Cast<AAIController>(OwnerComp.GetOwner());
	if (!Controller)
	{
		UE_LOG(LogTemp, Log, TEXT("no controller"));
		return EBTNodeResult::Type::Failed;
	}

	IAbilitySystemInterface* Interface = Cast<IAbilitySystemInterface>(Controller->GetPawn());
	if (!Interface)
	{
		UE_LOG(LogTemp, Log, TEXT("no interface"));
		return EBTNodeResult::Type::Failed;
	}

	CurrentASC = Interface->GetAbilitySystemComponent();

	if (AbilityTags.Num() == 0)
	{
		UE_LOG(LogTemp, Log, TEXT("no tag"));
		return EBTNodeResult::Type::Failed;
	}

	int32 index = FMath::RandRange(0, AbilityTags.Num() - 1);
	FGameplayTag AbilityTag = AbilityTags[index];

	SpecHandle = Interface->GetAbilitySpecHandleByTag(AbilityTag);
	if (!SpecHandle.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("no ability handle"));
		return EBTNodeResult::Type::Failed;
	}

	FGameplayAbilitySpec* Spec = CurrentASC->FindAbilitySpecFromHandle(SpecHandle);
	CurrentASC->OnAbilityEnded.AddLambda(
		[&](const FAbilityEndedData& AbilityData)
		{
			if (AbilityData.AbilitySpecHandle == SpecHandle)
			{
				CurrentASC->OnAbilityEnded.Clear();
				FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
			}
		}
	);

	CurrentASC->TryActivateAbility(SpecHandle);

	return EBTNodeResult::Type::InProgress;
}