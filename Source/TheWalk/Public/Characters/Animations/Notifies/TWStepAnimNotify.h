// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "TWStepAnimNotify.generated.h"

UCLASS()
class THEWALK_API UTWStepAnimNotify final : public UAnimNotify
{
    GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                        const FAnimNotifyEventReference& EventReference) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TMap<UPhysicalMaterial*, USoundBase*> Sounds;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    USoundBase* DefaultSound;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    FName SocketName;

    const float TraceDistance = 100.0f;

    bool LineTrace(const USkeletalMeshComponent* MeshComp, FHitResult& OutHit) const;
};
