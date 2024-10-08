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
	if (Attribute == GetStunWeightAttribute())
	{
		SetStunWeightValue(NewValue);
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

void UMatrixCharacterAttributeSet::SetStunWeightValue(float& Value)
{
	if (OnOverStunWeight.IsBound())
	{
		UE_LOG(LogTemp, Log, TEXT("bound"));

	}

	if (Value >= GetMaxStunWeight())
	{
		UE_LOG(LogTemp, Log, TEXT("Over stun weight"));
		OnOverStunWeight.Broadcast();
		Value = 0;
	}
}