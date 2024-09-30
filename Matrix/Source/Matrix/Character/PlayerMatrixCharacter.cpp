// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerMatrixCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AbilitySystemComponent.h"

#include "../Component/ItemHoldComponent.h"

APlayerMatrixCharacter::APlayerMatrixCharacter()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ItemHold->RegistEquipSocket(TEXT("EquipmentSocket_1"));
}

void APlayerMatrixCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	InputCompo = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// Set up action bindings
	if (InputCompo) 
	{
		// Jumping
		//InputCompo->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		//InputCompo->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		InputCompo->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerMatrixCharacter::Move);

		// Looking
		InputCompo->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerMatrixCharacter::Look);

		for (int32 i = 0; i < InputAbilityActivationInfos.Num(); i++)
		{
			InputCompo->BindAction(InputAbilityActivationInfos[i].GetInputAction(), ETriggerEvent::Started,
				this, &APlayerMatrixCharacter::StartInputAbility, i);
			InputCompo->BindAction(InputAbilityActivationInfos[i].GetInputAction(), ETriggerEvent::Completed,
				this, &APlayerMatrixCharacter::EndInputAbility, i);
		}
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlayerMatrixCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < InputAbilityActivationInfos.Num(); i++)
	{
		AddAbility(InputAbilityActivationInfos[i], i);
	}
}

void APlayerMatrixCharacter::AddAbility(FAbilityActivationInfo Info, int32 InputID)
{
	FGameplayAbilitySpec Spec(Info.GetAbility());
	Spec.InputID = InputID;
	FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(Spec);
	AbilitySpecHandles.Add(Info.GetTag(), Handle);
}

void APlayerMatrixCharacter::StartInputAbility(int InputID)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputID);
	if (Spec)
	{
		Spec->InputPressed = true;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			ASC->TryActivateAbility(Spec->Handle);
		}
	}
}

void APlayerMatrixCharacter::EndInputAbility(int InputID)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputID);
	if (Spec)
	{
		Spec->InputPressed = false;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputReleased(*Spec);
		}
	}
}

void APlayerMatrixCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerMatrixCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}