// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ItemHoldComponent.h"

#include "../Enum/ItemHoldType.h"
#include "../Interface/Equipment.h"
#include "../Interface/Hold.h"

// Sets default values for this component's properties
UItemHoldComponent::UItemHoldComponent()
{
	CurrentHoldObject = nullptr;

	CurrentHoldType = EItemHoldType::UnHold;
}

void UItemHoldComponent::Equip(TScriptInterface<IEquipment> Equipment)
{
	if (IsCurrentEquipment(Equipment))
		return;

	FName EquipSocket;
	if (TryGetUesableEquipSocket(EquipSocket) == false)
		return;

	FAttachmentTransformRules AttachmentRule(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		true);
	if (Equipment->GetEquipActor()->AttachToComponent(OwnerMesh, AttachmentRule, EquipSocket))
		UE_LOG(LogTemp, Log, TEXT("success attach"));
	//Equipment->GetEquipActor()->AddActorLocalTransform(Equipment->GetEquipOffsetTransform());
	Equipment->GetEquipActor()->SetActorRelativeTransform(Equipment->GetEquipOffsetTransform());
	CurrentEquipments[EquipSocket] = Equipment->GetEquipActor();
	Equipment->Equipment(GetOwner());

	OnEquipItem.Broadcast(Equipment);
}

void UItemHoldComponent::UnEquip(TScriptInterface<IEquipment> Equipment)
{
	if (IsCurrentEquipment(Equipment) == false)
		return;

	for (auto Pair : CurrentEquipments)
	{
		if (!Pair.Value)
			continue;

		if (Pair.Value == Equipment->GetEquipActor())
		{
			Pair.Value = nullptr;
			Equipment->Equipment(GetOwner());

			return;
		}
	}
}

bool UItemHoldComponent::IsCurrentEquipment(TScriptInterface<IEquipment> Equipment)
{
	for (const auto Pair : CurrentEquipments)
	{
		if (!Pair.Value)
			continue;

		if (Pair.Value == Equipment->GetEquipActor())
		{
			return true;
		}
	}

	return false;
}

void UItemHoldComponent::RegistEquipSocket(FName Socket)
{
	if (CurrentEquipments.Contains(Socket))
		return;

	CurrentEquipments.Add(Socket, nullptr);
}

bool UItemHoldComponent::TryGetUesableEquipSocket(FName& Result)
{
	for (const auto Pair : CurrentEquipments)
	{
		if (Pair.Value == nullptr)
		{
			Result = Pair.Key;
			return true;
		}
	}

	return false;
}

TScriptInterface<IEquipment> UItemHoldComponent::GetEquipment(int index)
{
	int idx = 0;
	for (const auto Pair : CurrentEquipments)
	{
		if (idx == index)
			return Pair.Value;

		idx++;
	}

	return nullptr;
}

void UItemHoldComponent::Hold(TScriptInterface<IHold> HoldObject)
{
	AActor* HoldActor = HoldObject->GetHoldActor();

	if (CurrentHoldObject)
	{
		if (HoldActor == CurrentHoldObject->GetHoldActor())
		{
			return;
		}
		else
		{
			UnHold();
		}
	}

	FAttachmentTransformRules AttachmentRule(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		true);
	HoldActor->AttachToComponent(OwnerMesh, AttachmentRule, HoldSocket);
	//HoldObject->GetHoldActor()->AddActorLocalTransform(HoldObject->GetHoldOffsetTransform());
	HoldObject->GetHoldActor()->SetActorRelativeTransform(HoldObject->GetHoldOffsetTransform());
	CurrentHoldObject = HoldObject;
	CurrentHoldType = HoldObject->GetHoldType();
	HoldObject->Hold(GetOwner());

	OnHoldItem.Broadcast(HoldObject);
}

void UItemHoldComponent::UnHold()
{
	if (!CurrentHoldObject)
		return;

	TScriptInterface<IEquipment> EquipObject = CurrentHoldObject->GetHoldActor();
	if (EquipObject)
	{
		if (IsCurrentEquipment(EquipObject))
		{
			for (const auto Pair : CurrentEquipments)
			{
				if (Pair.Value == EquipObject->GetEquipActor())
				{
					FAttachmentTransformRules AttachmentRule(
						EAttachmentRule::SnapToTarget,
						EAttachmentRule::SnapToTarget,
						EAttachmentRule::KeepWorld,
						true);
					EquipObject->GetEquipActor()->AttachToComponent(OwnerMesh, AttachmentRule, Pair.Key);
					EquipObject->GetEquipActor()->AddActorLocalTransform(EquipObject->GetEquipOffsetTransform());
				}
			}
		}
	}

	CurrentHoldObject->UnHold();
	CurrentHoldObject = nullptr;
	CurrentHoldType = EItemHoldType::UnHold;
}

void UItemHoldComponent::SetHoldSocket(FName Socket)
{
	HoldSocket = Socket;
}