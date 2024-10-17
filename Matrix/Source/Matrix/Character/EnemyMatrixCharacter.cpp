// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyMatrixCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"

#include "../Controller/MatrixAIController.h"
#include "../Ability/Attribute/MatrixCharacterAttributeSet.h"
#include "../Component/ItemHoldComponent.h"

void AEnemyMatrixCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ItemHold)
	{
		ItemHold->SetHoldSocket(TEXT("HoldSocket"));
		ItemHold->RegistEquipSocket(TEXT("EquipmentSocket_1"));
	}
}

void AEnemyMatrixCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AttributeSet)
	{
		AttributeSet->OnDamaged.AddDynamic(this, &AEnemyMatrixCharacter::OnDamaged);
	}
}

AMatrixAIController* AEnemyMatrixCharacter::GetMatrixAI()
{
	return Cast<AMatrixAIController>(GetController());
}

void AEnemyMatrixCharacter::OnDamaged(float Value)
{
	AAIController* AI = Cast<AAIController>(GetController());
	UBlackboardComponent* Blackboard = AI->GetBlackboardComponent();
	float RecentDamageAmount = Blackboard->GetValueAsFloat(RecentDamageAmountName);
	Blackboard->SetValueAsFloat(RecentDamageAmountName, RecentDamageAmount + Value);
}
