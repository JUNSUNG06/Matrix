// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Attribute/MatrixCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "../../Tag/MatrixTag.h"

UMatrixCharacterAttributeSet::UMatrixCharacterAttributeSet() :
	MaxHealth(100.0f),
	MaxHealthCount(2.0f),
	Damage(0.0f),
	StunWeightDescAmount(30.0f),
	StunWeightDescDelay(3.0f)
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
		OnHealthChanged.Broadcast(OldValue, NewValue, GetMaxHealth());
	}
	else if (Attribute == GetStunWeightAttribute())
	{
		OnStunWeightChanged.Broadcast(OldValue, NewValue, GetMaxStunWeight());

		if (NewValue >= OldValue)
		{
			GetWorld()->GetTimerManager().ClearTimer(StunWeightDescDelayTimer);
			GetWorld()->GetTimerManager().ClearTimer(StunWeightDescTimer);

			GetWorld()->GetTimerManager().SetTimer(
				StunWeightDescDelayTimer,
				this,
				&UMatrixCharacterAttributeSet::StartDescStunWeight,
				GetStunWeightDescDelay()
			);
		}
	}
	else if (Attribute == GetHealthCountAttribute())
	{
		OnHealthCountChanged.Broadcast(OldValue, NewValue, GetMaxHealthCount());

		if (NewValue > 0)
		{
			SetHealth(GetMaxHealth());
		}
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
			Data
		);

		OnDamaged.Broadcast(
			Data.EffectSpec.GetContext().GetEffectCauser(),
			Data.EvaluatedData.Magnitude
		);

		SetDamage(0.0f);
	}
}

void UMatrixCharacterAttributeSet::StartDescStunWeight()
{
	GetWorld()->GetTimerManager().SetTimer(
		StunWeightDescTimer,
		this,
		&UMatrixCharacterAttributeSet::DescStunWeight,
		GetWorld()->GetDeltaSeconds(),
		true
	);
}

void UMatrixCharacterAttributeSet::DescStunWeight()
{
	if (GetStunWeight() <= 0.0f)
	{
		SetStunWeight(0.0f);
		GetWorld()->GetTimerManager().ClearTimer(StunWeightDescTimer);
	}

	const float DescAmount = GetStunWeightDescAmount() * GetWorld()->GetDeltaSeconds();
	SetStunWeight(GetStunWeight() - DescAmount);
}

void UMatrixCharacterAttributeSet::SetHealthValue(float Value, const FGameplayEffectModCallbackData& Data)
{
	float PrevValue = GetHealth();

	SetHealth(Value);

	if (GetHealth() <= 0.0f)
	{
		SetHealthCount(GetHealthCount() - 1);

		if (GetHealthCount() <= 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Die"));
			Data.Target.TryActivateAbilitiesByTag(FGameplayTagContainer(ABILITY_CHARACTER_DIE));
			OnDie.Broadcast();
		}
	}
}