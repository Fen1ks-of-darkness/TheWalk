// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Controllers/TWPlayerController.h"
#include "TWGamePlayerController.generated.h"

UCLASS(Abstract)
class THEWALK_API ATWGamePlayerController final : public ATWPlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
