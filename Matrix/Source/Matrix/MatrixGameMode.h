// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Interface/GameCycle.h"

#include "MatrixGameMode.generated.h"

UCLASS(minimalapi)
class AMatrixGameMode : public AGameModeBase, public IGameCycle
{
	GENERATED_BODY()

public:
	AMatrixGameMode();

public:
	virtual void Clear_Implementation() override;
	virtual void Fail_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOnGameClear OnGameClear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOnGameFail OnGameFail;
};