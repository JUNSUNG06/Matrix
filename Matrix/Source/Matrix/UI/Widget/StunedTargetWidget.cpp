// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/StunedTargetWidget.h"

void UStunedTargetWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Collapsed);
}

void UStunedTargetWidget::SetOwnerActor(AActor* NewOwnerActor)
{
	Super::SetOwnerActor(NewOwnerActor);

	ABaseMatrixCharacter* MC = Cast<ABaseMatrixCharacter>(OwnerActor);
	if (MC)
	{
		MC->AbilityActivateDelegates[StunTag].AddDynamic(this, &UStunedTargetWidget::OnStun);
		MC->AbilityActivateDelegates[ClutchedTag].AddDynamic(this, &UStunedTargetWidget::OnClutched);
	}
}

void UStunedTargetWidget::Show_Implementation()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UStunedTargetWidget::Hide_Implementation()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UStunedTargetWidget::OnStun_Implementation(EAbilityActivateType AbilityActivateType)
{
	if (AbilityActivateType == EAbilityActivateType::Activate)
	{
		Show();
	}
	else if(AbilityActivateType == EAbilityActivateType::End)
	{
		Hide();
	}
}

void UStunedTargetWidget::OnClutched_Implementation(EAbilityActivateType AbilityActivateType)
{
	
}