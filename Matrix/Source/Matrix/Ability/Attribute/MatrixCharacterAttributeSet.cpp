// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Attribute/MatrixCharacterAttributeSet.h"

UMatrixCharacterAttributeSet::UMatrixCharacterAttributeSet() :
	MaxHealth(100.0f)
{
	InitHealth(GetMaxHealth());
}

void UMatrixCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

void UMatrixCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("Health : %f -> %f"), OldValue, NewValue);
	}
}
