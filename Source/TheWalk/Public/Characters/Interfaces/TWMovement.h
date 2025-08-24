// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TWMovement.generated.h"

UENUM(BlueprintType)
enum class ETWMovementType : uint8
{
    Walking,
    Running
};

UINTERFACE(MinimalAPI)
class UTWMovement : public UInterface
{
    GENERATED_BODY()
};

class THEWALK_API ITWMovement
{
    GENERATED_BODY()

public:
    virtual void SetMovementType(const ETWMovementType& InMovementType) = 0;
    virtual bool IsInAir() const = 0;
    virtual bool IsCrouch() const = 0;
};
