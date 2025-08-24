// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Controllers/TWGamePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Core/Settings/TWGameSettings.h"

void ATWGamePlayerController::BeginPlay()
{
    Super::BeginPlay();

    UEnhancedInputLocalPlayerSubsystem* EnhancedInput =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (EnhancedInput)
    {
        EnhancedInput->ClearAllMappings();

        const UTWGameSettings* GameSettings = GetDefault<UTWGameSettings>();
        check(GameSettings);
        EnhancedInput->AddMappingContext(GameSettings->InputMappingContext.LoadSynchronous(), 0);
    }
}
