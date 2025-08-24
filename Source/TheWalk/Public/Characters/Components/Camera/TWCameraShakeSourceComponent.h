// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShakeSourceComponent.h"
#include "TWCameraShakeSourceComponent.generated.h"

UCLASS()
class THEWALK_API UTWCameraShakeSourceComponent final : public UCameraShakeSourceComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings",
              meta = (ClampMin = "0.05", UIMin = "0.05", ClampMax = "1.0", UIMax = "1.0"))
    float Threshold = 0.1f;
};
