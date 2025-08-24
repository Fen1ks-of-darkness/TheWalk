// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/TWCharacter.h"
#include "Characters/Components/TWCharacterMovementComponent.h"

ATWCharacter::ATWCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UTWCharacterMovementComponent>(CharacterMovementComponentName))
{
}
