// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/PlayerWidget.h"

#include "../../Character/BaseMatrixCharacter.h"
#include "../../Ability/Attribute/MatrixCharacterAttributeSet.h"
#include "MatrixProgressBar.h"

void UPlayerWidget::SetOwnerActor(AActor* NewOwnerActor)
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

	Attribute->OnHealthChanged.AddDynamic(this, &UPlayerWidget::OnHealthChange);
}

void UPlayerWidget::SetHealthPercent(float Value, bool Immediately)
{
	PB_Health->SetPercent(Value, Immediately);
}

void UPlayerWidget::OnHealthChange(float Prev, float New, float Max)
{
	PB_Health->SetPercent(New / Max);
}