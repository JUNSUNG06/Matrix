// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"

#include "AbilitySystemComponent.h"

#include "MatrixCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOverStunWeight);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamaged, float, DamageAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChanged, float, PrevHealth, float, NewHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStunWeightChanged, float, PrevStunWeight, float, NewStunWeight, float, MaxStunWeight);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthCountChanged, float, PrevCount, float, NewCount, float, MaxCount);

/**
 * 
 */
UCLASS()
class MATRIX_API UMatrixCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UMatrixCharacterAttributeSet();

public:
	ATTRIBUTE_ACCESSORS(UMatrixCharacterAttributeSet, MaxWalkSpeed);
	ATTRIBUTE_ACCESSORS(UMatrixCharacterAttributeSet, MaxSprintSpeed);
	ATTRIBUTE_ACCESSORS(UMatrixCharacterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UMatrixCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UMatrixCharacterAttributeSet, MaxHealthCount);
	ATTRIBUTE_ACCESSORS(UMatrixCharacterAttributeSet, HealthCount);
	ATTRIBUTE_ACCESSORS(UMatrixCharacterAttributeSet, MaxStunWeight);
	ATTRIBUTE_ACCESSORS(UMatrixCharacterAttributeSet, StunWeight);
	ATTRIBUTE_ACCESSORS(UMatrixCharacterAttributeSet, StunWeightDescAmount);
	ATTRIBUTE_ACCESSORS(UMatrixCharacterAttributeSet, StunWeightDescDelay);
	ATTRIBUTE_ACCESSORS(UMatrixCharacterAttributeSet, Damage);

public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
		override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float
		NewValue) override;

	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

protected:
	virtual void StartDescStunWeight();
	virtual void DescStunWeight();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Move", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxWalkSpeed;
	UPROPERTY(BlueprintReadOnly, Category = "Move", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSprintSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealthCount;
	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData HealthCount;

	UPROPERTY(BlueprintReadOnly, Category = "Stun", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStunWeight;
	UPROPERTY(BlueprintReadOnly, Category = "Stun", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StunWeight;
	UPROPERTY(BlueprintReadOnly, Category = "Stun", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StunWeightDescAmount;
	UPROPERTY(BlueprintReadOnly, Category = "Stun", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StunWeightDescDelay;

	UPROPERTY(BlueprintReadOnly, Category = "Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;


public:
	FOverStunWeight OnOverStunWeight;
	FOnDie OnDie;
	FOnDamaged OnDamaged;
	FOnHealthChanged OnHealthChanged;
	FOnStunWeightChanged OnStunWeightChanged;
	FOnHealthCountChanged OnHealthCountChanged;
	
private:
	FTimerHandle StunWeightDescDelayTimer;
	FTimerHandle StunWeightDescTimer;

private:
	void SetHealthValue(float Value, const FGameplayEffectModCallbackData& Data);
};
