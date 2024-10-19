// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseMatrixCharacter.h"
#include "EnemyMatrixCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API AEnemyMatrixCharacter : public ABaseMatrixCharacter
{
	GENERATED_BODY()

public:
	AEnemyMatrixCharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	class AMatrixAIController* GetMatrixAI();

public:
	virtual void OnLockOned_Implementation() override;
	virtual void OnEndLockOned_Implementation() override;

protected:
	UFUNCTION()
	void OnDamaged(float Value);

public:
	UPROPERTY(EditAnywhere, Category = BT)
	FName RecentDamageAmountName;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent> LockOnedWidget;
};
