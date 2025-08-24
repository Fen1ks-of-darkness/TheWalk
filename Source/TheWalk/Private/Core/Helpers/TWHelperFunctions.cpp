// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/Helpers/TWHelperFunctions.h"
#include "EnhancedActionKeyMapping.h"
#include "GameFramework/InputSettings.h"
#include "InputAction.h"
#include "InputMappingContext.h"

FText FTWHelperFunctions::GetDisplayNameByAction(const UInputMappingContext* InputMappingContext,
                                                 const UInputAction* Action)
{
    check(InputMappingContext);
    const TArray<FEnhancedActionKeyMapping>& Mappings = InputMappingContext->GetMappings();

    for (const FEnhancedActionKeyMapping& Mapping : Mappings)
    {
        if (Mapping.Action == Action)
        {
            return Mapping.Key.GetDisplayName();
        }
    }
    return FText();
}
