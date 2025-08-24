// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Interfaces/TWPlayerPawn.h"
#include "Characters/TWCharacter.h"
#include "TWPlayerCharacter.generated.h"

class UInputAction;
class UTWCameraComponent;
class USpringArmComponent;
class UTWCharacterTrajectoryComponent;
class UTWCameraShakeSourceComponent;
class USceneComponent;
struct FInputActionInstance;
struct FInputActionValue;

UCLASS(Abstract)
class THEWALK_API ATWPlayerCharacter final : public ATWCharacter, public ITWPlayerPawn
{
    GENERATED_BODY()

public:
    ATWPlayerCharacter(const FObjectInitializer& ObjInit);
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void AddControllerPitchInput(const float value) override;
    virtual void AddControllerYawInput(const float value) override;
    virtual UCapsuleComponent* GetPlayerCapsule_Implementation() override;
    virtual UCharacterMovementComponent* GetPlayerCharacterMovement_Implementation() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UTWCameraComponent* CameraComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* CameraBoom;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UTWCharacterTrajectoryComponent* TrajectoryComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UTWCameraShakeSourceComponent* CameraShakeSourceComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USceneComponent* FlashlightSceneComponent;

    UPROPERTY(EditAnywhere, Category = "Settings")
    bool bIsPlayerInTrigger = false;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    UInputAction* MovementAction;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    UInputAction* LookAction;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    UInputAction* JumpAction;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    UInputAction* CrouchAction;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    UInputAction* RunAction;

    void Move(const FInputActionValue& ActionValue);
    void Look(const FInputActionValue& ActionValue);
    void CrouchPressed(const FInputActionInstance& Instance);
    void CrouchReleased(const FInputActionInstance& Instance);
    void SetMovementType(const ETWMovementType& MovementType);
};
