// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "InputMappingContext.h"
#include "TWGameSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "'Game Settings'"))
class THEWALK_API UTWGameSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UPROPERTY(Config, EditDefaultsOnly, Category = "Settings")
    TSoftObjectPtr<UInputMappingContext> InputMappingContext;
};
