// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatrixCharacter.h"
#include "AbilitySystemInterface.h"
#include "GameplayTags.h"
#include "GameplayAbilitySpecHandle.h"

#include "../Interface/ItemHoldInterface.h"

#include "BaseMatrixCharacter.generated.h"
/**
 * 
 */
UCLASS()
class MATRIX_API ABaseMatrixCharacter : public AMatrixCharacter, public IAbilitySystemInterface, 
	public IItemHoldInterface
{
	GENERATED_BODY()
	
public:
	ABaseMatrixCharacter();

public:
	virtual void BeginPlay() override;

	//GAS
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual FGameplayAbilitySpecHandle GetAbilitySpecHandleByTag(FGameplayTag Tag) override;

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

protected:
	UPROPERTY(EditAnywhere, Category = GAS, meta = (PrivateAccessAllow = true))
	TMap<FGameplayTag, TSubclassOf<class UGameplayAbility>> Abilities;

	TMap<FGameplayTag, FGameplayAbilitySpecHandle> AbilitySpecHandles;

	//ItemHold
public:
	virtual UItemHoldComponent* GetItemHoldComponent() override;

protected:
	UPROPERTY(EditAnywhere, Category = ItemHold)
	TObjectPtr<class UItemHoldComponent> ItemHold;
};