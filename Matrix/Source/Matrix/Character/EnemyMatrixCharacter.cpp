// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyMatrixCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Components/WidgetComponent.h"

#include "../Controller/MatrixAIController.h"
#include "../Ability/Attribute/MatrixCharacterAttributeSet.h"
#include "../Component/ItemHoldComponent.h"

AEnemyMatrixCharacter::AEnemyMatrixCharacter()
{
	LockOnedWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockOnedWidget"));
	LockOnedWidget->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, 
		FName("LockOnedWidgetSocket")
	);
}

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

	if (LockOnedWidget)
	{
		if (LockOnedWidget->GetWidget())
		{
			UE_LOG(LogTemp, Log, TEXT("asdasdasdasd"));
			LockOnedWidget->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

AMatrixAIController* AEnemyMatrixCharacter::GetMatrixAI()
{
	return Cast<AMatrixAIController>(GetController());
}

void AEnemyMatrixCharacter::OnLockOned_Implementation()
{
	Super::OnLockOned_Implementation();

	if (LockOnedWidget && LockOnedWidget->GetWidget())
	{
		LockOnedWidget->GetWidget()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void AEnemyMatrixCharacter::OnEndLockOned_Implementation()
{
	Super::OnEndLockOned_Implementation();

	if (LockOnedWidget && LockOnedWidget->GetWidget())
	{
		LockOnedWidget->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AEnemyMatrixCharacter::OnDamaged(float Value)
{
	AAIController* AI = Cast<AAIController>(GetController());
	UBlackboardComponent* Blackboard = AI->GetBlackboardComponent();
	float RecentDamageAmount = Blackboard->GetValueAsFloat(RecentDamageAmountName);
	Blackboard->SetValueAsFloat(RecentDamageAmountName, RecentDamageAmount + Value);
}
