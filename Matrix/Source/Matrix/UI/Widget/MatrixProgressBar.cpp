// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MatrixProgressBar.h"
#include "Components/ProgressBar.h"

UMatrixProgressBar::UMatrixProgressBar()
{
	FollowSpeed = 1.0f;
}

void UMatrixProgressBar::SetPercent(float Value, bool Immediately)
{
	PB_Top->SetPercent(Value);

	GetWorld()->GetTimerManager().ClearTimer(FollowTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(FollowHandle);

	if (Immediately)
	{
		PB_Bottom->SetPercent(Value);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(
			FollowTimerHandle,
			this,
			&UMatrixProgressBar::StartFollow,
			FollowTime);
	}
}

void UMatrixProgressBar::StartFollow()
{
	GetWorld()->GetTimerManager().SetTimer(
		FollowHandle,
		this,
		&UMatrixProgressBar::Follow,
		GetWorld()->GetDeltaSeconds(),
		true);
}

void UMatrixProgressBar::Follow()
{
	const float Dest = PB_Top->GetPercent();
	const float Cur = PB_Bottom->GetPercent();
	float Next = Cur - GetWorld()->GetDeltaSeconds() * FollowSpeed;
	if (FMath::Abs(Next - Dest) <= GetWorld()->GetDeltaSeconds() * FollowSpeed)
	{
		Next = Dest;

		GetWorld()->GetTimerManager().ClearTimer(FollowHandle);
	}

	PB_Bottom->SetPercent(Next);
}