// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Interface/Interact.h"

#include "ItemActor.generated.h"

class UItemDataAsset;

UCLASS()
class MATRIX_API AItemActor : public AActor, public IInteract
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

public:
	virtual void Interact(AActor* interactor) override;

protected:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	AActor* OwnerActor;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PrivateAccessAllow))
	TObjectPtr<UItemDataAsset> Data;

public:
	FORCEINLINE void SetOwner(AActor* NewOwner) { OwnerActor = NewOwner; }

	template<typename T>
	FORCEINLINE TObjectPtr<T> GetData() { return Cast<T>(Data); }
	FORCEINLINE TObjectPtr<UItemDataAsset> GetData() { return Data; }
};
