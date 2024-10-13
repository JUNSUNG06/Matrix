// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Attribute/MatrixCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "../../Tag/MatrixTag.h"

UMatrixCharacterAttributeSet::UMatrixCharacterAttributeSet() :
	MaxHealth(100.0f),
	MaxHealthCount(2.0f),
	Damage(0.0f)
{
	InitHealth(GetMaxHealth());
	InitMaxStunWeight(100.0f);
	InitHealthCount(GetMaxHealthCount());
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
		OnHealthChanged.Broadcast(OldValue, NewValue);
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

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		if (GetHealth() <= 0.0f)
		{
			SetHealth(GetMaxHealth());
			SetHealthCount(GetHealthCount() - 1);

			if (GetHealthCount() <= 0.0f)
			{
				UE_LOG(LogTemp, Log, TEXT("Die"));
				Data.Target.TryActivateAbilitiesByTag(FGameplayTagContainer(ABILITY_CHARACTER_DIE));
				OnDie.Broadcast();
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetStunWeightAttribute())
	{
		if (GetStunWeight() >= GetMaxStunWeight())
		{
			Data.Target.TryActivateAbilitiesByTag(FGameplayTagContainer(ABILITY_CHARACTER_STARTSTUN));
			OnOverStunWeight.Broadcast();
			SetStunWeight(0.0f);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("Damaged"));
		SetHealthValue(
			FMath::Clamp(GetHealth() - Data.EvaluatedData.Magnitude, 0.0f, GetMaxHealth()),
			Data);
		OnDamaged.Broadcast(Data.EvaluatedData.Magnitude);
		SetDamage(0.0f);
	}
}

void UMatrixCharacterAttributeSet::SetHealthValue(float Value, const FGameplayEffectModCallbackData& Data)
{
	float PrevValue = GetHealth();

	SetHealth(Value);

	if (GetHealth() <= 0.0f)
	{
		SetHealth(GetMaxHealth());
		SetHealthCount(GetHealthCount() - 1);

		if (GetHealthCount() <= 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Die"));
			Data.Target.TryActivateAbilitiesByTag(FGameplayTagContainer(ABILITY_CHARACTER_DIE));
			OnDie.Broadcast();
		}
	}
}
