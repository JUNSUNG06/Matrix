// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponItemActor.h"

#include "../Interface/ItemHoldInterface.h"
#include "../Component/ItemHoldComponent.h"
#include "../DataAsset/Item/WeaponItemDataAsset.h"


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

void AWeaponItemActor::Hold()
{
}

void AWeaponItemActor::UnHold()
{
}

AActor* AWeaponItemActor::GetHoldActor()
{
	return this;
}

EItemHoldType AWeaponItemActor::GetHoldType()
{
	return HoldType;
}

void AWeaponItemActor::Equipment()
{
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