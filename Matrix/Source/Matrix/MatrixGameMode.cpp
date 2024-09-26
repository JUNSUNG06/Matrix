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
