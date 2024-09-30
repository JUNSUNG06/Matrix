// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GAAT_TraceTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceResultDelegate, const
	FGameplayAbilityTargetDataHandle&, TargetDataHandle);

/**
 * 
 */
UCLASS()
class MATRIX_API UGAAT_TraceTarget : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UGAAT_TraceTarget();

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName =
		"WaitForTrace", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility",
		BlueprintInternalUseOnly = "TRUE"))
	static UGAAT_TraceTarget* CreateTask(UGameplayAbility* OwningAbility, 
		TSubclassOf<class AGATA_SphereTrace> TargetActorClass);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

public:
	void SpawnAndInitializeTargetActor();
	void FinalizeTargetActor();

public:
	void SetTraceData(float Range, float Radius);

protected:
	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle);

public:
	UPROPERTY(BlueprintAssignable)
	FTraceResultDelegate OnComplete;

protected:
	UPROPERTY()
	TSubclassOf<class AGATA_SphereTrace> TargetActorClass;

	UPROPERTY()
	TObjectPtr<class AGATA_SphereTrace> SpawnedTargetActor;

private:
	float TraceRange;
	float TraceRadius;
};
