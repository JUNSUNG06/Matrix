// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyMatrixCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include"AIController.h"

#include "../Enum/EnemyStateType.h"

void AEnemyMatrixCharacter::Stun()
{
	Super::Stun();
	UE_LOG(LogTemp, Log, TEXT("Stun"));

	AAIController* AI = Cast<AAIController>(GetController());
	UBlackboardComponent* Blackboard = AI->GetBlackboardComponent();
	Blackboard->SetValueAsEnum(StatePropertyName, (uint8)EEnemyStateType::Stun);
}