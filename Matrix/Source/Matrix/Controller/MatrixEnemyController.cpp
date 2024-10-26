// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MatrixEnemyController.h"

#include "../UI/Widget/EnemyWidget.h"
#include "../UI/HUD/MatrixHUD.h"
#include "../Character/BaseMatrixCharacter.h"

void AMatrixEnemyController::BeginPlay()
{
	Super::BeginPlay();

	EnemyWidget = CreateWidget<UEnemyWidget>(GetWorld(), EnemyWidgetClass);
	EnemyWidget->SetOwnerActor(this);
	EnemyWidget->SetHealthPercent(1.0f, true);
	EnemyWidget->SetStunWeightPercent(0.0f);
	AMatrixHUD* HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AMatrixHUD>();
	if (HUD)
	{
		HUD->AddWidget(EnemyWidget);
		HUD->HideWidget(EnemyWidget);
	}

	GetMatrixCharacter()->OnStartedBattle.AddDynamic(this, &AMatrixEnemyController::OnStartBattle);
}

void AMatrixEnemyController::OnStartBattle()
{
	AMatrixHUD* HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AMatrixHUD>();
	if (HUD)
	{
		HUD->ShowWidget(EnemyWidget);
	}
}
