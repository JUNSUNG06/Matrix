// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/ActorUserWidget.h"
#include "GameplayTags.h"

#include "../../Character/BaseMatrixCharacter.h"

#include "StunedTargetWidget.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UStunedTargetWidget : public UActorUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	virtual void SetOwnerActor(AActor* NewOwnerActor) override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void Show();
	virtual void Show_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	void Hide();
	virtual void Hide_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void OnStun(EAbilityActivateType AbilityActivateType);
	virtual void OnStun_Implementation(EAbilityActivateType AbilityActivateType);

	UFUNCTION(BlueprintNativeEvent)
	void OnClutched(EAbilityActivateType AbilityActivateType);
	virtual void OnClutched_Implementation(EAbilityActivateType AbilityActivateType);

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag StunTag;
	UPROPERTY(EditAnywhere)
	FGameplayTag ClutchedTag;
};
