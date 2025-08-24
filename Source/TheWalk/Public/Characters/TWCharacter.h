// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/Interfaces/TWMovement.h"
#include "TWCharacter.generated.h"

UCLASS(Abstract)
class THEWALK_API ATWCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    explicit ATWCharacter(const FObjectInitializer& ObjInit);
};
