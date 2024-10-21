// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MatrixPlayerController.h"

#include "../UI/Widget/MatrixUserWidget.h"
#include "../UI/HUD/MatrixHUD.h"
#include "../UI/Widget/PlayerWidget.h"
#include "../MatrixGameMode.h"

void AMatrixPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerWidget = CreateWidget<UPlayerWidget>(this, PlayerWidgetClass);
	PlayerWidget->SetOwnerActor(this);
	PlayerWidget->SetHealthPercent(1.0f, true);
	GetMatrixHUD()->AddWidget(PlayerWidget);

	GetMatrixGameMode()->OnGameClear.AddDynamic(this, &AMatrixPlayerController::OnGameClear);
	GetMatrixGameMode()->OnGameFail.AddDynamic(this, &AMatrixPlayerController::OnGameFail);
}

void AMatrixPlayerController::OnGameClear()
{
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);

	UMatrixUserWidget* ClearWidget = CreateWidget<UMatrixUserWidget>(GetWorld(), ClearWidgetClass);
	GetMatrixHUD()->AddWidget(ClearWidget);
	
}

void AMatrixPlayerController::OnGameFail()
{
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);

	UMatrixUserWidget* FailWidget = CreateWidget<UMatrixUserWidget>(GetWorld(), FailWidgetClass);
	GetMatrixHUD()->AddWidget(FailWidget);
}
