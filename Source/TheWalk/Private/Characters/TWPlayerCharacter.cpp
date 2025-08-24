// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/TWPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/Components/Camera/TWCameraComponent.h"
#include "Characters/Components/Camera/TWCameraShakeSourceComponent.h"
#include "Characters/Components/TWCharacterMovementComponent.h"
#include "Characters/Components/TWCharacterTrajectoryComponent.h"

void ATWPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (GetClass()->ImplementsInterface(UTWPlayerPawn::StaticClass()))
    {
        ITWPlayerPawn::Execute_GetPlayerCapsule(this);
        ITWPlayerPawn::Execute_GetPlayerCharacterMovement(this);
    }
}

ATWPlayerCharacter::ATWPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    check(CameraBoom);
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UTWCameraComponent>(TEXT("CameraComponent"));
    check(CameraComponent);
    CameraComponent->bUsePawnControlRotation = false;
    CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

    TrajectoryComponent = CreateDefaultSubobject<UTWCharacterTrajectoryComponent>(TEXT("CharacterTrajectoryComponent"));

    FlashlightSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("FlashlightSceneComponent"));
    check(FlashlightSceneComponent);
    FlashlightSceneComponent->SetupAttachment(GetMesh());

    CameraShakeSourceComponent =
        CreateDefaultSubobject<UTWCameraShakeSourceComponent>(TEXT("CameraShakeSourceComponent"));
    check(CameraShakeSourceComponent);
    CameraShakeSourceComponent->SetupAttachment(GetRootComponent());

    bUseControllerRotationYaw = false;
    check(GetCharacterMovement());
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

UCapsuleComponent* ATWPlayerCharacter::GetPlayerCapsule_Implementation()
{
    return GetCapsuleComponent();
}

UCharacterMovementComponent* ATWPlayerCharacter::GetPlayerCharacterMovement_Implementation()
{
    return GetCharacterMovement();
}

void ATWPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(MovementAction);
    check(LookAction);
    check(JumpAction);
    check(CrouchAction);
    check(RunAction);

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    check(EnhancedInputComponent);
    EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
    EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ThisClass::CrouchPressed);
    EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ThisClass::CrouchReleased);
}

void ATWPlayerCharacter::Move(const FInputActionValue& ActionValue)
{
    FVector2D Input = ActionValue.Get<FVector2D>();

    if (Controller && !FMath::IsNearlyZero(Input.SizeSquared()))
    {
        const FRotator ControlRotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, ControlRotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, Input.Y);
        AddMovementInput(RightDirection, Input.X);
    }
}

void ATWPlayerCharacter::SetMovementType(const ETWMovementType& MovementType)
{
    ITWMovement* Movement = Cast<ITWMovement>(GetCharacterMovement());
    check(Movement);
    Movement->SetMovementType(MovementType);
}

void ATWPlayerCharacter::Look(const FInputActionValue& ActionValue)
{
    if (!FMath::IsNearlyZero(ActionValue.GetMagnitude()))
    {
        AddControllerPitchInput(ActionValue[1]);
        AddControllerYawInput(ActionValue[0]);
    }
}

void ATWPlayerCharacter::AddControllerPitchInput(const float value)
{
    Super::AddControllerPitchInput(value);
}

void ATWPlayerCharacter::AddControllerYawInput(const float value)
{
    Super::AddControllerYawInput(value);
}

void ATWPlayerCharacter::CrouchPressed(const FInputActionInstance& Instance)
{
    Super::Crouch();
}

void ATWPlayerCharacter::CrouchReleased(const FInputActionInstance& Instance)
{
    Super::UnCrouch();
}