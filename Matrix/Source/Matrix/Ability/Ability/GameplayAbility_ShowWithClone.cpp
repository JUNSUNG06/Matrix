// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ability/GameplayAbility_ShowWithClone.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

#include "../../Character/CloneEnemyMatrixCharacter.h"

void UGameplayAbility_ShowWithClone::OnCompleteQuery(TSharedPtr<struct FEnvQueryResult> Result)
{
	Super::OnCompleteQuery(Result);

	TArray<FVector> ShowPoints;
	Result->GetAllAsLocations(ShowPoints);

	int OwnerIndex = FMath::RandRange(0, ShowPoints.Num() - 1);
	for (int i = 0; i < ShowPoints.Num(); i++)
	{
		if (i == OwnerIndex)
		{
			GetAvatarActorFromActorInfo()->SetActorLocation(ShowPoints[i]);
		}
		else
		{
			GetWorld()->SpawnActor<ACloneEnemyMatrixCharacter>();
		}
	}
}