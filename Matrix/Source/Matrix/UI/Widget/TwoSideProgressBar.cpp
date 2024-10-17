// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/TwoSideProgressBar.h"
#include "Components/ProgressBar.h"

void UTwoSideProgressBar::SetPercent(float Value)
{
	Percent = Value;

	PB_Left->SetPercent(Percent);
	PB_Right->SetPercent(Percent);
}

float UTwoSideProgressBar::GetPercent()
{
	return Percent;
}
