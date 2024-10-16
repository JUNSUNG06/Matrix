// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MatrixProgressBar.h"
#include "Components/ProgressBar.h"

void UMatrixProgressBar::SetPercent(float Value, bool Immediately)
{
	PB_Top->SetPercent(Value);

	GetWorld()->GetTimerManager().ClearTimer(FollowTimerHandle);

	GetWorld()->GetTimerManager().SetTimer(
		FollowTimerHandle,
		this,
		&UMatrixProgressBar::Follow,
		FollowTime);
}

void UMatrixProgressBar::Follow()
{
	PB_Bottom->SetPercent(PB_Top->GetPercent());
}