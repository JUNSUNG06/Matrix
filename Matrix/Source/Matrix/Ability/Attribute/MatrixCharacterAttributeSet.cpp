// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Attribute/MatrixCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"

#include "../../Tag/MatrixTag.h"

UMatrixCharacterAttributeSet::UMatrixCharacterAttributeSet() :
	MaxHealth(100.0f),
	MaxHealthCount(1.0f),
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
		if (OldValue == NewValue)
			return;

		UE_LOG(LogTemp, Log, TEXT("Health : %f -> %f"), OldValue, NewValue);

		OnHealthChanged.Broadcast(OldValue, NewValue, GetMaxHealth());

		if (NewValue <= 0.0f)
		{
			SetHealthCount(GetHealthCount() - 1);
		}
	}
	else if (Attribute == GetHealthCountAttribute())
	{
		OnHealthCountChanged.Broadcast(OldValue, NewValue, GetMaxHealthCount());

		if (NewValue > 0.0f)
		{
			SetHealth(GetMaxHealth());
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Die"));
			
			GetOwningAbilitySystemComponent()->TryActivateAbilitiesByTag(
				FGameplayTagContainer(ABILITY_CHARACTER_DIE));

			OnDie.Broadcast();
		}
	}
	else if (Attribute == GetStunWeightAttribute())
	{
		OnStunWeightChanged.Broadcast(OldValue, NewValue, GetMaxStunWeight());

		if (NewValue >= OldValue)
		{
			GetWorld()->GetTimerManager().ClearTimer(StunWeightDescDelayTimer);
			GetWorld()->GetTimerManager().ClearTimer(StunWeightDescTimer);

			if (NewValue >= GetMaxStunWeight())
			{
				GetOwningAbilitySystemComponent()->TryActivateAbilitiesByTag(
					FGameplayTagContainer(ABILITY_CHARACTER_STARTSTUN));
				OnOverStunWeight.Broadcast();
				SetStunWeight(0.0f);
			}
			else
			{
				GetWorld()->GetTimerManager().SetTimer(
					StunWeightDescDelayTimer,
					this,
					&UMatrixCharacterAttributeSet::StartDescStunWeight,
					GetStunWeightDescDelay()
				);
			}
		}
	}
}

bool UMatrixCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
		return false; 

	if (GetOwningAbilitySystemComponent()->HasMatchingGameplayTag(ABILITY_CHARACTER_DODGE))
	{
		Data.EvaluatedData.Magnitude = 0.0f;
	}

	return true;
}

void UMatrixCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		if (Data.EvaluatedData.Magnitude <= 0.0f)
			return;

		UE_LOG(LogTemp, Log, TEXT("Damaged"));
		SetHealth(
			FMath::Clamp(
				GetHealth() - Data.EvaluatedData.Magnitude,
				0.0f, GetMaxHealth())
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