// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseMatrixCharacter.h"

#include "AbilitySystemComponent.h"
#include "../Component/ItemHoldComponent.h"
#include "../Struct/Ability/AbilityInformation.h"

ABaseMatrixCharacter::ABaseMatrixCharacter()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));

	ItemHold = CreateDefaultSubobject<UItemHoldComponent>(TEXT("ItemHold"));
}

void ABaseMatrixCharacter::BeginPlay()
{
	Super::BeginPlay();

	ASC->InitAbilityActorInfo(this, this);
	for (FAbilityActivationInfo const Info : AbilityActivationInfos)
	{
		AddAbility(Info);
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

void ABaseMatrixCharacter::AddAbility(FAbilityActivationInfo Info, int32 InputID)
{
	FGameplayAbilitySpec Spec(Info.GetAbility());
	FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(Spec);
	AbilitySpecHandles.Add(Info.GetTag(), Handle);
}

void ABaseMatrixCharacter::RemoveAbility(FAbilityActivationInfo Info)
{
	FGameplayAbilitySpecHandle Handle = GetAbilitySpecHandleByTag(Info.GetTag());
	if (Handle.IsValid())
	{
		ASC->ClearAbility(Handle);
	}
}

UItemHoldComponent* ABaseMatrixCharacter::GetItemHoldComponent()
{
	return ItemHold;
}
