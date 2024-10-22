// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MatrixPlayerController.generated.h"

UENUM(BlueprintType)
enum class EInputMappingContextType : uint8
{
	Default UMETA(DisplayName = "Default"),
	UI UMETA(DisplayName = "UI"),
};

UCLASS()
class MATRIX_API AMatrixPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void BeginPlay() override;

	//Input
public:
	void ChangeMappingContext(EInputMappingContextType Type);

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TMap<EInputMappingContextType, class UInputMappingContext*> MappingContexts;
	EInputMappingContextType CurrentMappingContextType;

	class UEnhancedInputLocalPlayerSubsystem* Subsystem;

	//Widget
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerWidget> PlayerWidgetClass;
	UPROPERTY()
	TObjectPtr<class UPlayerWidget> PlayerWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMatrixUserWidget> PauseWidgetClass;
	TObjectPtr<class UMatrixUserWidget> PauseWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMatrixUserWidget> ClearWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMatrixUserWidget> FailWidgetClass;


	//GameCycle
protected:
	UFUNCTION()
	void OnGameClear();
	UFUNCTION()
	void OnGameFail();
	UFUNCTION()
	void OnGamePause(bool IsPause);

	//Utils
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE class AMatrixHUD* GetMatrixHUD() { return GetHUD<class AMatrixHUD>(); }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE class AMatrixGameMode* GetMatrixGameMode() { return Cast<AMatrixGameMode>(GetWorld()->GetAuthGameMode()); }
};
