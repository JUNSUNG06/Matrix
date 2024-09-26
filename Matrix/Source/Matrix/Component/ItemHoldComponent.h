// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../Enum/HoldType.h"

#include "ItemHoldComponent.generated.h"

class IEquip;
class IHold;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipmentItem, TScriptInterface<IEquipment>, NewEquipItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHoldItem, TScriptInterface<IHold>, NewHoldItem);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MATRIX_API UItemHoldComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemHoldComponent();

	//Equip
public:
	UFUNCTION(BlueprintCallable)
	void Equip(TScriptInterface<IEquipment> Equipment);
	UFUNCTION(BlueprintCallable)
	void UnEquip(TScriptInterface<IEquipment> Equipment);
	UFUNCTION(BlueprintCallable)
	bool IsCurrentEquipment(TScriptInterface<IEquipment> Equipment);
	UFUNCTION(BlueprintCallable)
	void RegistEquipSocket(FName Socket);

protected:
	bool TryGetUesableEquipSocket(FName& Result);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, meta = (PrivateAccessAllow))
	TMap<FName, AActor*> CurrentEquipments;

public:
	TScriptInterface<IEquipment> GetEquipment(int index);

	//Hold
public:
	UFUNCTION(BlueprintCallable)
	void Hold(TScriptInterface<IHold> HoldObject);
	UFUNCTION(BlueprintCallable)
	void UnHold();
	UFUNCTION(BlueprintCallable)
	void SetHoldSocket(FName Socket);

protected:
	TScriptInterface<IHold> CurrentHoldObject;

	FName HoldSocket;

public:
	FORCEINLINE TScriptInterface<IHold> GetCurrentHoldObject() const { return CurrentHoldObject; };

	//OwnerMesh
public:
	FORCEINLINE void SetOwnerMesh(class USkeletalMeshComponent* Mesh) { OwnerMesh = Mesh; };

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, meta = (PrivateAccessAllow))
	TObjectPtr<class USkeletalMeshComponent> OwnerMesh;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	EItemHoldType CurrentHoldType;

public:
	FORCEINLINE EItemHoldType GetCurrentHoldType() const { return CurrentHoldType; }

public:
	UPROPERTY(BlueprintAssignable)
	FOnEquipmentItem OnEquipItem;

	UPROPERTY(BlueprintAssignable)
	FOnHoldItem OnHoldItem;
};
