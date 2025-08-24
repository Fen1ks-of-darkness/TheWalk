// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/Interfaces/TWMovement.h"
#include "TWCharacterMovementComponent.generated.h"

UCLASS()
class THEWALK_API UTWCharacterMovementComponent final : public UCharacterMovementComponent, public ITWMovement
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
    ETWMovementType MovementType = ETWMovementType::Walking;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
    bool bCanMove = true;

    virtual void SetMovementType(const ETWMovementType& InMovementType) override;
    virtual float GetMaxSpeed() const override;
    virtual bool IsInAir() const override;
    virtual bool IsCrouch() const override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TMap<ETWMovementType, float> Speeds{
        {ETWMovementType::Walking, 200.0f},
        {ETWMovementType::Running, 400.0f}
    };
};
