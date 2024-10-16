// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/TwoSideProgressBar.h"
#include "Components/ProgressBar.h"

void UTwoSideProgressBar::SetPercent(float Value)
{
	PB_Left->SetPercent(Value);
	PB_Right->SetPercent(Value);
}