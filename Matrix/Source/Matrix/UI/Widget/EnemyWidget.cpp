// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/EnemyWidget.h"

#include "../../Character/BaseMatrixCharacter.h"
#include "../../Ability/Attribute/MatrixCharacterAttributeSet.h"
#include "MatrixProgressBar.h"
#include "TwoSideProgressBar.h"
#include "HealthCountContainer.h"

void UEnemyWidget::SetOwnerActor(AActor* NewOwnerActor)
{
	Super::SetOwnerActor(NewOwnerActor);

	AController* Controller = Cast<AController>(NewOwnerActor);
	if (!Controller)
		return;
	ABaseMatrixCharacter* Character = Cast<ABaseMatrixCharacter>(Controller->GetPawn());
	if (!Character)
		return;
	UMatrixCharacterAttributeSet* Attribute = Character->GetAttributeSet();
	if (!Attribute)
		return;

	Attribute->OnHealthChanged.AddDynamic(this, &UEnemyWidget::OnHealthChange);
	Attribute->OnStunWeightChanged.AddDynamic(this, &UEnemyWidget::OnStunWeightChange);
	Attribute->OnHealthCountChanged.AddDynamic(this, &UEnemyWidget::OnHealthCountChange);

	SetHealthCount(Attribute->GetMaxHealthCount());
}

void UEnemyWidget::SetHealthPercent(float Value, bool Immediately)
{
	PB_Health->SetPercent(Value, Immediately);
}

void UEnemyWidget::SetStunWeightPercent(float Value)
{
	TSPB_StunWeight->SetPercent(Value);
}

void UEnemyWidget::SetHealthCount(int Count)
{
	C_HealthCount->SetHealthCount(Count);
}

void UEnemyWidget::UseHealthCount()
{
	C_HealthCount->Use();
}

void UEnemyWidget::OnHealthChange(float Prev, float New, float Max)
{
	PB_Health->SetPercent(New / Max);
}

void UEnemyWidget::OnStunWeightChange(float Prev, float New, float Max)
{
	TSPB_StunWeight->SetPercent(New / Max);
}

void UEnemyWidget::OnHealthCountChange(float Prev, float New, float Max)
{
	if (New < Prev)
	{
		for (int i = 0; i < Prev - New; i++)
		{
			C_HealthCount->Use();
		}
	}
	else if (Prev > New)
	{
		C_HealthCount->SetHealthCount(New);
	}
}
