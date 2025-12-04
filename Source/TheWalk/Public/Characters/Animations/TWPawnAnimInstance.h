// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/Interfaces/TWMovement.h"
#include "TWPawnAnimInstance.generated.h"

UCLASS(Abstract)
class THEWALK_API UTWPawnAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Speed = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Direction = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Yaw = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Pitch = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    bool bIsFalling = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    bool bIsCroucing = false;

    UPROPERTY()
    APawn* Pawn;

    ITWMovement* Movement;
};
