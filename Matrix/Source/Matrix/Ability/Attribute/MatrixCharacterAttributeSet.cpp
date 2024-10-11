// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Attribute/MatrixCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "../../Tag/MatrixTag.h"

UMatrixCharacterAttributeSet::UMatrixCharacterAttributeSet() :
	MaxHealth(100.0f)
{
	InitHealth(GetMaxHealth());
	InitMaxStunWeight(100.0f);
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

bool UMatrixCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
		return false; 

	return true;
}

void UMatrixCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetStunWeightAttribute())
	{
		if (GetStunWeight() >= GetMaxStunWeight())
		{
			UE_LOG(LogTemp, Log, TEXT("Over stun weight"));
			Data.Target.TryActivateAbilitiesByTag(FGameplayTagContainer(ABILITY_CHARACTER_STARTSTUN));
			OnOverStunWeight.Broadcast();
			SetStunWeight(0.0f);
		}
	}
}