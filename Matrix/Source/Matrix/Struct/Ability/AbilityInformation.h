// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTags.h"

#include "AbilityInformation.generated.h"

UCLASS()
class MATRIX_API AAbilityInformation : public AActor
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FAbilityActivationInfo
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PrivateAccessAllow = true))
	TSubclassOf<class UGameplayAbility> Ability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PrivateAccessAllow = true))
	class UInputAction* InputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PrivateAccessAllow = true))
	FGameplayTag Tag;

public:
	inline class TSubclassOf<class UGameplayAbility> GetAbility() const { return Ability; }
	inline class UInputAction* GetInputAction() const { return InputAction; }
	inline FGameplayTag GetTag() const { return Tag; }

public:
	bool operator==(FAbilityActivationInfo& Right);
};
