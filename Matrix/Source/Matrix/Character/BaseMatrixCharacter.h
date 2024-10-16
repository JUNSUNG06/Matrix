// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatrixCharacter.h"
#include "AbilitySystemInterface.h"
#include "GameplayTags.h"
#include "GameplayAbilitySpecHandle.h"

#include "../Interface/ItemHoldInterface.h"
#include "../Struct/Ability/AbilityInformation.h"
#include "../Interface/LockOnTarget.h"

#include "BaseMatrixCharacter.generated.h"
/**
 * 
 */
UCLASS()
class MATRIX_API ABaseMatrixCharacter : public AMatrixCharacter, public IAbilitySystemInterface, 
	public IItemHoldInterface, public ILockOnTarget
{
	GENERATED_BODY()
	
public:
	ABaseMatrixCharacter();

public:
	virtual void BeginPlay() override;

	//GAS
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual FGameplayAbilitySpecHandle GetAbilitySpecHandleByTag(FGameplayTag Tag) override;

	virtual void AddAbility(const FAbilityActivationInfo& Info);
	virtual void RemoveAbility(const FAbilityActivationInfo& Info);

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MotionWarping)
	TObjectPtr<class UMotionWarpingComponent> MotionWarping;

public:
	FORCEINLINE UMotionWarpingComponent* GetMotionWarping() { return MotionWarping; }

protected:
	UPROPERTY(EditAnywhere, Category = GAS, meta = (PrivateAccessAllow = true))
	TArray<FAbilityActivationInfo> StartAbilityActivationInfos;
	
	UPROPERTY(VisibleAnywhere, Category = GAS, meta = (PrivateAccessAllow = true))
	TArray<FAbilityActivationInfo> CurrentAbilityActivationInfos;

	UPROPERTY()
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY()
	TObjectPtr<class UMatrixCharacterAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PrivateAccessAllow = true))
	TObjectPtr<class UMCAttributeSetDataAsset> AttributeSetData;

public:
	class UMatrixCharacterAttributeSet* GetAttributeSet() { return AttributeSet; }

	//ItemHold
public:
	virtual UItemHoldComponent* GetItemHoldComponent() override;

protected:
	UPROPERTY(EditAnywhere, Category = ItemHold)
	TObjectPtr<class UItemHoldComponent> ItemHold;

	//LockOn
public:
	UFUNCTION(BlueprintCallable)
	virtual FVector GetLockOnTransform_Implementation() const override;
	UFUNCTION(BlueprintCallable)
	virtual AActor* GetLockOnActor_Implementation() override;
	UFUNCTION(BlueprintCallable)
	virtual bool CanLockOn_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Target;
};