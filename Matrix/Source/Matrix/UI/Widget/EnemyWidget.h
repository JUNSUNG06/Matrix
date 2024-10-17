// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/ActorUserWidget.h"
#include "EnemyWidget.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API UEnemyWidget : public UActorUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	virtual void SetOwnerActor(AActor* NewOwnerActor) override;

	void SetHealthPercent(float Value, bool Immediately = false);
	void SetStunWeightPercent(float Value);
	void SetHealthCount(int Count);
	void UseHealthCount();

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UMatrixProgressBar* PB_Health;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTwoSideProgressBar* TSPB_StunWeight;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UHealthCountContainer* C_HealthCount;

protected:
	UFUNCTION()
	void OnHealthChange(float Prev, float New, float Max);

	UFUNCTION()
	void OnStunWeightChange(float Prev, float New, float Max);

	UFUNCTION()
	void OnHealthCountChange(float Prev, float New, float Max);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDie();
};
