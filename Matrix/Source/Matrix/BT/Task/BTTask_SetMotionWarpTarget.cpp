// Fill out your copyright notice in the Description page of Project Settings.


#include "BT/Task/BTTask_SetMotionWarpTarget.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "MotionWarpingComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_SetMotionWarpTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	FVector TargetPoint;

	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		TargetPoint = BlackboardComp->
			GetValueAsVector(BlackboardKey.SelectedKeyName) + Offset;

	}
	else if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		const UObject* TargetObject = BlackboardComp->
			GetValueAsObject(BlackboardKey.SelectedKeyName);
		const AActor* TargetActor = Cast<AActor>(TargetObject);
		TargetPoint = TargetActor->GetActorLocation() + Offset;
	}
	else
	{
		return EBTNodeResult::Type::Failed;

	}

	const AActor* SelfActor = OwnerComp.GetAIOwner()->GetPawn();
	UMotionWarpingComponent* WM = SelfActor->GetComponentByClass<UMotionWarpingComponent>();
	if (!WM)
	{
		return EBTNodeResult::Type::Failed;

	}

	FMotionWarpingTarget WarpTarget = {};
	WarpTarget.Name = TargetName;
	WarpTarget.Location = TargetPoint;

	WM->AddOrUpdateWarpTarget(WarpTarget);

	return EBTNodeResult::Type::Succeeded;
}