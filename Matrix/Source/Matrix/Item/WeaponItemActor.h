// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemActor.h"

#include "../Interface/Hold.h"
#include "../Interface/Equipment.h"
#include "../Enum/ItemHoldType.h"

#include "WeaponItemActor.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API AWeaponItemActor : public AItemActor, public IHold, public IEquipment
{
	GENERATED_BODY()
	
public:
	AWeaponItemActor();

	//Interface
public:
	virtual void Interact(AActor* interactor) override;

	virtual void Hold(AActor* Performer) override;
	virtual void UnHold() override;
	virtual AActor* GetHoldActor() override;
	virtual EItemHoldType GetHoldType() override;

	virtual void Equipment(AActor* Performer) override;
	virtual void UnEquipment() override;
	virtual AActor* GetEquipActor() override;

	virtual FTransform GetEquipOffsetTransform() override;
	virtual FTransform GetHoldOffsetTransform() override;

public:
	virtual void OnAttack();
	virtual void AttackHitCheck();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PrivateAccessAllow = true))
	EItemHoldType HoldType;
};
