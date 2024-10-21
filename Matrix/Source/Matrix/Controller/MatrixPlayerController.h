// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MatrixPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MATRIX_API AMatrixPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnGameClear();
	UFUNCTION()
	void OnGameFail();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerWidget> PlayerWidgetClass;

	UPROPERTY()
	class UPlayerWidget* PlayerWidget;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMatrixUserWidget> ClearWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMatrixUserWidget> FailWidgetClass;

	//Utils
public:
	FORCEINLINE class AMatrixHUD* GetMatrixHUD() { return GetHUD<class AMatrixHUD>(); }
	FORCEINLINE class AMatrixGameMode* GetMatrixGameMode() { return Cast<AMatrixGameMode>(GetWorld()->GetAuthGameMode()); }

};
