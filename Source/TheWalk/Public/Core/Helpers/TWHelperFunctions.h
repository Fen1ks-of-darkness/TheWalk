// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UInputAction;
class UInputMappingContext;

class THEWALK_API FTWHelperFunctions final
{
public:
    template <class T>
    static T* GetComponentByInterface(const AActor* Actor)
    {
        if (Actor)
        {
            const TArray<UActorComponent*> ActorComponents =
                Actor->GetComponentsByInterface(T::UClassType::StaticClass());
            if (ActorComponents.Num() > 0)
            {
                return Cast<T>(ActorComponents[0]);
            }
            checkNoEntry();
        }
        return nullptr;
    }

    template <class T>
    static TArray<T*> GetComponentsByInterface(const AActor* Actor)
    {
        TArray<T*> InterfacesComponents;
        if (Actor)
        {
            const TArray<UActorComponent*> ActorComponents =
                Actor->GetComponentsByInterface(T::UClassType::StaticClass());
            for (UActorComponent* ActorComponent : ActorComponents)
            {
                InterfacesComponents.Add(Cast<T>(ActorComponent));
            }
        }
        return InterfacesComponents;
    }

    static FText GetDisplayNameByAction(const UInputMappingContext* InputMappingContext, const UInputAction* Action);
};
