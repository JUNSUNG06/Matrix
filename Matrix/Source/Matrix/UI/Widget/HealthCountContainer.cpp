// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/HealthCountContainer.h"
#include "Components/HorizontalBox.h"

#include "HealthCount.h"

UHealthCountContainer::UHealthCountContainer()
{
	HealthCounts = {};
}

void UHealthCountContainer::SetHealthCount(int Count)
{
	CurrentIndex = Count - 1;

	for (int i = HealthCounts.Num(); i < Count; i++)
	{
		UHealthCount* HealthCountInst = CreateWidget<UHealthCount>(GetWorld(), HealthCountClass);
		HB_CountContainer->AddChild(HealthCountInst);
		HealthCounts.Add(HealthCountInst);
	}

	for (int i = Count; i < HealthCounts.Num() - 1; i++)
	{
		HealthCounts[i]->SetVisibility(ESlateVisibility::Collapsed);
	}

	for (int i = 0; i < Count; i++)
	{
		HealthCounts[i]->Reset();
	}
}

void UHealthCountContainer::Use()
{
	if (CurrentIndex < 0)
		return;

	HealthCounts[CurrentIndex]->Use();
	CurrentIndex--;
}