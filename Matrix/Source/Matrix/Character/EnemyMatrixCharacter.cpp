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
#include "../Component/ActorWidgetComponent.h"
#include "../Interface/GameCycle.h"

AEnemyMatrixCharacter::AEnemyMatrixCharacter()
{
	LockOnedWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockOnedWidget"));
	LockOnedWidget->SetupAttachment(GetMesh(), FName("LockOnedWidgetSocket"));

	StunedWidget = CreateDefaultSubobject<UActorWidgetComponent>(TEXT("StunedWidget"));
	StunedWidget->SetupAttachment(GetMesh(), FName("LockOnedWidgetSocket"));
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

	if (LockOnedWidget)
	{
		if (LockOnedWidget->GetWidget())
		{
			LockOnedWidget->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	if (StunedWidget)
	{
		StunedWidget->SetOwnerActor(this);
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

void AEnemyMatrixCharacter::OnDamaged(AActor* Attacker, float Damage)
{
	Super::OnDamaged(Attacker, Damage);

	AAIController* AI = Cast<AAIController>(GetController());
	UBlackboardComponent* Blackboard = AI->GetBlackboardComponent();
	float RecentDamageAmount = Blackboard->GetValueAsFloat(RecentDamageAmountName);
	Blackboard->SetValueAsFloat(RecentDamageAmountName, RecentDamageAmount + Damage);
}

void AEnemyMatrixCharacter::OnDie()
{
	Super::OnDie();

	if (GetMatrixGameMode())
	{
		IGameCycle::Execute_Clear(GetMatrixGameMode());
	}
}

void AEnemyMatrixCharacter::OnSetTarget_Implementation(AActor* PrevTarget, AActor* NewTarget)
{
	if (!PrevTarget && NewTarget)
	{
		StartBattle();
	}
}
