// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Components/TWCharacterMovementComponent.h"

void UTWCharacterMovementComponent::SetMovementType(const ETWMovementType& InMovementType)
{
    MovementType = InMovementType;
}

float UTWCharacterMovementComponent::GetMaxSpeed() const
{
    check(Speeds.Contains(MovementType));
    return Speeds[MovementType];
}

bool UTWCharacterMovementComponent::IsInAir() const
{
    return IsFalling();
}

bool UTWCharacterMovementComponent::IsCrouch() const
{
    return IsCrouching();
}
