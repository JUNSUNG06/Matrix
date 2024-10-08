// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MatrixCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AMatrixCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMatrixCharacter();

protected:
	virtual void BeginPlay();

public:
	void Freeze(float Time);

private:
	void EndFreeze();

private:
	FTimerHandle FreezeTimer;
};

