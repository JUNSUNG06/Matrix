// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemActor.h"

// Sets default values
AItemActor::AItemActor()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    Mesh->SetupAttachment(RootComponent);
}

void AItemActor::Interact(AActor* interactor)
{
    SetOwner(interactor);
}