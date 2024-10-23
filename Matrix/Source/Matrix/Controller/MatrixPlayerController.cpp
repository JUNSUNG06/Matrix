// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MatrixPlayerController.h"
#include "EnhancedInputSubsystems.h"

#include "../UI/Widget/MatrixUserWidget.h"
#include "../UI/HUD/MatrixHUD.h"
#include "../UI/Widget/PlayerWidget.h"
#include "../MatrixGameMode.h"

void AMatrixPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	ChangeMappingContext(EInputMappingContextType::Default);
}

void AMatrixPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerWidget = CreateWidget<UPlayerWidget>(this, PlayerWidgetClass);
	PlayerWidget->SetOwnerActor(this);
	PlayerWidget->SetHealthPercent(1.0f, true);
	GetMatrixHUD()->AddWidget(PlayerWidget);
	
	PauseWidget = CreateWidget<UMatrixUserWidget>(this, PauseWidgetClass);
	GetMatrixHUD()->AddWidget(PauseWidget);
	PauseWidget->SetVisibility(ESlateVisibility::Collapsed);

	GetMatrixGameMode()->OnGameClear.AddDynamic(this, &AMatrixPlayerController::OnGameClear);
	GetMatrixGameMode()->OnGameFail.AddDynamic(this, &AMatrixPlayerController::OnGameFail);
	GetMatrixGameMode()->OnGamePause.AddDynamic(this, &AMatrixPlayerController::OnGamePause);
}

void AMatrixPlayerController::ChangeMappingContext(EInputMappingContextType Type)
{
	if (!Subsystem)
	{
		return;
	}
	if (!MappingContexts[Type])
	{
		return;
	}

	Subsystem->RemoveMappingContext(MappingContexts[CurrentMappingContextType]);
	Subsystem->AddMappingContext(MappingContexts[EInputMappingContextType::Default], 0);
	CurrentMappingContextType = Type;
}

void AMatrixPlayerController::OnGameClear()
{
	UMatrixUserWidget* ClearWidget = CreateWidget<UMatrixUserWidget>(GetWorld(), ClearWidgetClass);
	GetMatrixHUD()->ShowWidget(ClearWidget);
}

void AMatrixPlayerController::OnGameFail()
{
	UMatrixUserWidget* FailWidget = CreateWidget<UMatrixUserWidget>(GetWorld(), FailWidgetClass);
	GetMatrixHUD()->ShowWidget(FailWidget);
}

void AMatrixPlayerController::OnGamePause(bool IsPause)
{
	if (IsPause)
	{
		ChangeMappingContext(EInputMappingContextType::UI);
		GetMatrixHUD()->ShowWidget(PauseWidget);
	}
	else
	{
		ChangeMappingContext(EInputMappingContextType::Default);
	}
}
