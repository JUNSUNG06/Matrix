// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseMatrixCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MotionWarpingComponent.h"

#include "../Component/ItemHoldComponent.h"
#include "../Struct/Ability/AbilityInformation.h"
#include "../Ability/Attribute/MatrixCharacterAttributeSet.h"
#include "../DataAsset/AttributeSet/MCAttributeSetDataAsset.h"

ABaseMatrixCharacter::ABaseMatrixCharacter()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));

	AttributeSet = CreateDefaultSubobject<UMatrixCharacterAttributeSet>(TEXT("AttributeSet"));

	MotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));

	ItemHold = CreateDefaultSubobject<UItemHoldComponent>(TEXT("ItemHold"));
	ItemHold->SetOwnerMesh(GetMesh());
}

void ABaseMatrixCharacter::BeginPlay()
{
	Super::BeginPlay();

	ASC->InitAbilityActorInfo(this, this);

	if (AttributeSet && AttributeSetData)
	{
		AttributeSet->InitMaxWalkSpeed(AttributeSetData->GetMaxWalkSpeed());
		AttributeSet->InitMaxSprintSpeed(AttributeSetData->GetMaxSprintSpeed());
		AttributeSet->InitHealth(100.0f);

		GetCharacterMovement()->MaxWalkSpeed = AttributeSet->GetMaxWalkSpeed();
	}

	for (const FAbilityActivationInfo Info : StartAbilityActivationInfos)
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
	if (AbilitySpecHandles.Contains(Tag))
		return AbilitySpecHandles[Tag];
	else
		return FGameplayAbilitySpecHandle();
}

void ABaseMatrixCharacter::AddAbility(const FAbilityActivationInfo& Info)
{
	CurrentAbilityActivationInfos.Add(Info);
	FGameplayAbilitySpec Spec(Info.GetAbility());
	FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(Spec);
	AbilitySpecHandles.Add(Info.GetTag(), Handle);
}

void ABaseMatrixCharacter::RemoveAbility(const FAbilityActivationInfo& Info)
{
	int32 index = CurrentAbilityActivationInfos.Find(Info);
	if (index == INDEX_NONE)
		return;

	CurrentAbilityActivationInfos.RemoveAt(index);

	FGameplayAbilitySpecHandle Handle = GetAbilitySpecHandleByTag(Info.GetTag());
	ASC->ClearAbility(Handle);

	AbilitySpecHandles.Remove(Info.GetTag());
}

UItemHoldComponent* ABaseMatrixCharacter::GetItemHoldComponent()
{
	return ItemHold;
}

FVector ABaseMatrixCharacter::GetLockOnTransform_Implementation() const
{
	return GetActorLocation();
}

AActor* ABaseMatrixCharacter::GetLockOnActor_Implementation()
{
	return this;
}

bool ABaseMatrixCharacter::CanLockOn_Implementation()
{
	return true;
}