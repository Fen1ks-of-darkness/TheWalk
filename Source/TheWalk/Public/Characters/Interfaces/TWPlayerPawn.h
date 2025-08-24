// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TWPlayerPawn.generated.h"

class UCapsuleComponent;
class UCharacterMovementComponent;

UINTERFACE(Blueprintable, MinimalAPI)
class UTWPlayerPawn : public UInterface
{
    GENERATED_BODY()
};

class THEWALK_API ITWPlayerPawn
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UCapsuleComponent* GetPlayerCapsule();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UCharacterMovementComponent* GetPlayerCharacterMovement();
};
