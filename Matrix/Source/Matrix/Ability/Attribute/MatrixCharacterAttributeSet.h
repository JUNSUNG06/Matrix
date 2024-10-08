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
	ATTRIBUTE_ACCESSORS(UMatrixCharacterAttributeSet, MaxStunWeight);
	ATTRIBUTE_ACCESSORS(UMatrixCharacterAttributeSet, StunWeight);

public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
		override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float
		NewValue) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Move", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxWalkSpeed;
	UPROPERTY(BlueprintReadOnly, Category = "Move", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSprintSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Stun", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStunWeight;
	UPROPERTY(BlueprintReadOnly, Category = "Stun", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StunWeight;

public:
	FOverStunWeight OnOverStunWeight;

private:
	void SetStunWeightValue(float& Value);
};
