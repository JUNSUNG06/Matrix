// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MatrixHUD.h"
#include "Blueprint/UserWidget.h"

#include "../Widget/MatrixUserWidget.h"
#include "MatrixGameMode.h"

void AMatrixHUD::BeginPlay()
{
	Super::BeginPlay();
}

void AMatrixHUD::AddWidget(UMatrixUserWidget* Widget)
{
	EWidgetType WidgetType = Widget->GetWidgetType();

	if (!Widgets.Contains(WidgetType))
		Widgets.Add(WidgetType, {});

	Widgets[WidgetType].Array.Add(Widget);
	Widget->AddToViewport();
}

void AMatrixHUD::ShowWidget(UMatrixUserWidget* Widget)
{
	if (!Widget)
		return;

	EWidgetType WidgetType = Widget->GetWidgetType();
	if (!Widgets[WidgetType].Array.Contains(Widget))
		AddWidget(Widget);

	if (WidgetType == EWidgetType::Game)
	{
		Widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else if (WidgetType == EWidgetType::Menu)
	{
		if (ActivateMenuWidget == Widget)
			return;

		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());;

		if (MenuWidgetStack.Num() > 0)
		{
			MenuWidgetStack[MenuWidgetStack.Num() - 1]->SetVisibility(ESlateVisibility::Collapsed);
		}

		Widget->SetVisibility(ESlateVisibility::Visible);
		MenuWidgetStack.Push(Widget);
		ActivateMenuWidget = Widget;
	}

	Widget->OnShow();
}

void AMatrixHUD::HideWidget(UMatrixUserWidget* Widget)
{
	if (!Widget)
		return;

	EWidgetType WidgetType = Widget->GetWidgetType();

	if (WidgetType == EWidgetType::Game)
	{
		Widget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else if (WidgetType == EWidgetType::Menu)
	{
		if (Widget != ActivateMenuWidget)
			return;

		Widget->SetVisibility(ESlateVisibility::Collapsed);

		MenuWidgetStack.Pop();

		if (MenuWidgetStack.Num() > 0)
		{
			MenuWidgetStack.Top()->SetVisibility(ESlateVisibility::Visible);
			ActivateMenuWidget = MenuWidgetStack.Top();
		}
		else
		{
			ActivateMenuWidget = nullptr;
		}
	}

	Widget->OnHide();
}

int AMatrixHUD::BackMenu()
{
	if (MenuWidgetStack.Num() == 0)
		return -1;

	HideWidget(ActivateMenuWidget);

	if (MenuWidgetStack.Num() == 0)
	{
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());;

	}

	return MenuWidgetStack.Num();
}