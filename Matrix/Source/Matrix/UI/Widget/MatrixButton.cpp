// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MatrixButton.h"
#include "Kismet/GameplayStatics.h"

UMatrixButton::UMatrixButton()
{
	OnHovered.AddDynamic(this, &UMatrixButton::OnHover);
	OnUnhovered.AddDynamic(this, &UMatrixButton::OnUnhover);
	OnClicked.AddDynamic(this, &UMatrixButton::OnClick);
}

void UMatrixButton::OnHover()
{
	SetColorAndOpacity(OnHoverColor);
	UGameplayStatics::PlaySound2D(GetWorld(), OnHoverSound);
}

void UMatrixButton::OnUnhover()
{
	SetColorAndOpacity(DefaultColor);
}

void UMatrixButton::OnClick()
{
	UGameplayStatics::PlaySound2D(GetWorld(), OnClickSound);
}