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
#include "../Interface/Damageable.h"
#include "../MatrixGameMode.h"

#include "BaseMatrixCharacter.generated.h"
/**
 * 
 */

UENUM()
enum class EAbilityActivateType : uint8
{
	Activate UMETA(DisplayName = "Activate"),
	End UMETA(DisplayName = "End"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivateAbility, EAbilityActivateType, AbilityActivateType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartBattle);

UCLASS()
class MATRIX_API ABaseMatrixCharacter : public AMatrixCharacter, public IAbilitySystemInterface, 
	public IItemHoldInterface, public ILockOnTarget, public IDamageable
{
	GENERATED_BODY()
	
public:
	ABaseMatrixCharacter();

public:
	virtual void BeginPlay() override;

protected:
	void StartBattle();

	UFUNCTION(BlueprintNativeEvent)
	void OnStartBattle();
	virtual void OnStartBattle_Implementation();

public:
	FOnStartBattle OnStartedBattle;

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

public:
	TMap<FGameplayTag, FOnActivateAbility> AbilityActivateDelegates;

protected:
	UPROPERTY(EditAnywhere, Category = GAS, meta = (PrivateAccessAllow = true))
	TArray<FAbilityActivationInfo> StartAbilityActivationInfos;
	
	UPROPERTY(VisibleAnywhere, Category = GAS, meta = (PrivateAccessAllow = true))
	TArray<FAbilityActivationInfo> CurrentAbilityActivationInfos;

protected:
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemHold)
	TObjectPtr<class UItemHoldComponent> ItemHold;

	//LockOn
public:
	virtual FVector GetLockOnTransform_Implementation() const override;
	virtual AActor* GetLockOnActor_Implementation() override;
	virtual bool CanLockOn_Implementation() override;
	virtual void OnLockOned_Implementation() override;
	virtual void OnEndLockOned_Implementation() override;

public:
	FOnLockOned OnLockOn;

public:
	UFUNCTION()
	virtual void OnDamaged(AActor* Attacker, float Damage) override;

public:
	UFUNCTION()
	virtual void OnDie();

protected:
	UPROPERTY()
	AActor* Target;

	UFUNCTION(BlueprintNativeEvent)
	void OnSetTarget(AActor* PrevTarget, AActor* NewTarget);
	virtual void OnSetTarget_Implementation(AActor* PrevTarget, AActor* NewTarget);

public:
	UFUNCTION(BlueprintCallable)
	inline AActor* GetTarget() { return Target; }
	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* NewTarget);

	//Utils
public:
	FORCEINLINE AMatrixGameMode* GetMatrixGameMode() { return Cast<AMatrixGameMode>(GetWorld()->GetAuthGameMode()); }
};