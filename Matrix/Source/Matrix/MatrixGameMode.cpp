// Copyright Epic Games, Inc. All Rights Reserved.

#include "MatrixGameMode.h"
#include "MatrixCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMatrixGameMode::AMatrixGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMatrixGameMode::Clear_Implementation()
{
	OnGameClear.Broadcast();
}

void AMatrixGameMode::Fail_Implementation()
{
	OnGameFail.Broadcast();
}

void AMatrixGameMode::Pause_Implementation(bool IsPause)
{
	bIsPaused = IsPause;

	GetWorldSettings()->SetTimeDilation(IsPause ? 0.0f : 1.0f);

	OnGamePause.Broadcast(IsPause);
}
