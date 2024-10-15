// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorWidgetComponent.h"

#include "../UI/Widget/ActorUserWidget.h"

void UActorWidgetComponent::BeginPlay()
{
	Super::InitWidget();

	UActorUserWidget* ActorWidget = Cast<UActorUserWidget>(GetWidget());
	if (ActorWidget)
	{
		ActorWidget->SetOwnerActor(GetOwner());
	}
}