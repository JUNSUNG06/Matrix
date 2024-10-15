// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MatrixHUD.h"
#include "Blueprint/UserWidget.h"

#include "../Widget/MatrixUserWidget.h"

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

	if (ActivateWidget == Widget)
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
		Widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	ActivateWidget = Widget;
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
		Widget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
