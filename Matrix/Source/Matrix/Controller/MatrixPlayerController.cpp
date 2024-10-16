// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MatrixPlayerController.h"

#include "../UI/Widget/MatrixUserWidget.h"
#include "../UI/HUD/MatrixHUD.h"
#include "../UI/Widget/PlayerWidget.h"

void AMatrixPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerWidget = CreateWidget<UPlayerWidget>(this, PlayerWidgetClass);
	PlayerWidget->SetOwnerActor(this);
	PlayerWidget->SetHealthPercent(1.0f, true);
	AMatrixHUD* HUD = GetHUD<AMatrixHUD>();
	if (HUD)
	{
		HUD->AddWidget(PlayerWidget);
	}
}
