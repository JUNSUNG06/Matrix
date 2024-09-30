// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATA_SphereTrace.generated.h"

DECLARE_DELEGATE_RetVal_OneParam(bool, FCheckCondition, AActor*)

/**
 * 
 */
UCLASS()
class MATRIX_API AGATA_SphereTrace : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	AGATA_SphereTrace();

public:
	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargetingAndContinue() override;

public:
	void SetTraceData(float Range, float Radius);

public:
	void SetShowDebug(bool InShowDebug) { bShowDebug = InShowDebug; }

protected:
	bool bShowDebug = false;

public:
	FCheckCondition CheckCondition;

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const;

private:
	float TraceRange;
	float TraceRadius;
};
