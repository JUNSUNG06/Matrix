// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponItemActor.h"

#include "../Interface/ItemHoldInterface.h"
#include "../Component/ItemHoldComponent.h"
#include "../DataAsset/Item/WeaponItemDataAsset.h"
#include "../Character/BaseMatrixCharacter.h"

AWeaponItemActor::AWeaponItemActor()
{

}

void AWeaponItemActor::Interact(AActor* interactor)
{
	Super::Interact(interactor);

	IItemHoldInterface* ItemHold = Cast<IItemHoldInterface>(interactor);
	if (ItemHold)
	{
		ItemHold->GetItemHoldComponent()->Equip(this);
	}
}

void AWeaponItemActor::Hold(AActor* Performer)
{
	SetOwner(Performer);

	SetActorEnableCollision(false);

	ABaseMatrixCharacter* Character = Cast<ABaseMatrixCharacter>(OwnerActor);
	if (!Character)
		return;

	TArray<FAbilityActivationInfo> AdditiveAbilities = GetData<UWeaponItemDataAsset>()->GetAdditiveAbility();
	for (int i = 0; i < AdditiveAbilities.Num(); i++)
	{
		Character->AddAbility(AdditiveAbilities[i]);
	}
}

void AWeaponItemActor::UnHold()
{
	ABaseMatrixCharacter* Character = Cast<ABaseMatrixCharacter>(OwnerActor);
	if (!Character)
		return;

	TArray<FAbilityActivationInfo> AdditiveAbilities = GetData<UWeaponItemDataAsset>()->GetAdditiveAbility();
	for (int i = 0; i < AdditiveAbilities.Num(); i++)
	{
		Character->RemoveAbility(AdditiveAbilities[i]);
	}
}

AActor* AWeaponItemActor::GetHoldActor()
{
	return this;
}

EItemHoldType AWeaponItemActor::GetHoldType()
{
	return HoldType;
}

void AWeaponItemActor::Equipment(AActor* Performer)
{
	SetOwner(Performer);

	SetActorEnableCollision(false);
}

void AWeaponItemActor::UnEquipment()
{
}

AActor* AWeaponItemActor::GetEquipActor()
{
	return this;
}

FTransform AWeaponItemActor::GetEquipOffsetTransform()
{
	return  GetData<UWeaponItemDataAsset>()->GetEquipSocketOffset();
}

FTransform AWeaponItemActor::GetHoldOffsetTransform()
{
	return GetData<UWeaponItemDataAsset>()->GetHoldSocketOffset();
}

void AWeaponItemActor::OnAttack()
{
	UE_LOG(LogTemp, Log, TEXT("try attack"));
}

void AWeaponItemActor::AttackHitCheck()
{

}