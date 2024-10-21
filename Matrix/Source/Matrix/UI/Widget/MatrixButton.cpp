// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MatrixButton.h"
#include "Kismet/GameplayStatics.h"

UMatrixButton::UMatrixButton()
{
	OnHovered.AddDynamic(this, &UMatrixButton::OnHover);
	OnUnhovered.AddDynamic(this, &UMatrixButton::OnUnhover);
	OnClicked.AddDynamic(this, &UMatrixButton::OnClick);

	OnHoverColor = FLinearColor(1.0f, 0.03f, 0.07f, 1.0f);
	DefaultColor = FLinearColor::White;

	ConstructorHelpers::FObjectFinder<USoundBase> ClickSoundRef(
		TEXT("/Game/Matrix/ETC/Sound/Cue/UI/SU_Button_Click.SU_Button_Click"));
	if (ClickSoundRef.Succeeded())
		OnClickSound = ClickSoundRef.Object;
	ConstructorHelpers::FObjectFinder<USoundBase> HoverSoundRef(
		TEXT("/Game/Matrix/ETC/Sound/Cue/UI/SU_Button_Hover.SU_Button_Hover"));
	if (HoverSoundRef.Succeeded())
		OnHoverSound = HoverSoundRef.Object;
}

void UMatrixButton::OnHover()
{
	SetColorAndOpacity(OnHoverColor);
	if(OnHoverSound)
		UGameplayStatics::PlaySound2D(GetWorld(), OnHoverSound);
}

void UMatrixButton::OnUnhover()
{
	SetColorAndOpacity(DefaultColor);
}

void UMatrixButton::OnClick()
{
	if(OnClickSound)
		UGameplayStatics::PlaySound2D(GetWorld(), OnClickSound);
}