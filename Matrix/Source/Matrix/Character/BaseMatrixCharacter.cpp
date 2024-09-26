// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseMatrixCharacter.h"

#include "AbilitySystemComponent.h"
#include "../Component/ItemHoldComponent.h"

ABaseMatrixCharacter::ABaseMatrixCharacter()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));

	ItemHold = CreateDefaultSubobject<UItemHoldComponent>(TEXT("ItemHold"));
}

void ABaseMatrixCharacter::BeginPlay()
{
	Super::BeginPlay();

	ASC->InitAbilityActorInfo(this, this);
	for (auto const Pair : Abilities)
	{
		FGameplayAbilitySpec Spec(Pair.Value);
		FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(Spec);
		AbilitySpecHandles.Add(Pair.Key, Handle);
	}
}

UAbilitySystemComponent* ABaseMatrixCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

FGameplayAbilitySpecHandle ABaseMatrixCharacter::GetAbilitySpecHandleByTag(FGameplayTag Tag)
{
	return AbilitySpecHandles[Tag];
}
