// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MatrixPlayerController.h"
#include "Blueprint/UserWidget.h"

#include "../UI/Widget/MatrixUserWidget.h"
#include "../UI/HUD/MatrixHUD.h"

void AMatrixPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerWidget = CreateWidget<UMatrixUserWidget>(this, PlayerWidgetClass);
	AMatrixHUD* HUD = GetHUD<AMatrixHUD>();
	if (HUD)
	{
		HUD->AddWidget(PlayerWidget);
	}
}
