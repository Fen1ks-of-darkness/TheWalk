// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Animations/Notifies/TWStepAnimNotify.h"
#include "Kismet/GameplayStatics.h"

void UTWStepAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                               const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    // Step Sounds
    FHitResult OutHit;
    if (LineTrace(MeshComp, OutHit))
    {
        const UPhysicalMaterial* PhysicalMaterial = OutHit.PhysMaterial.Get();
        USoundBase* Sound = Sounds.Contains(PhysicalMaterial) ? Sounds[PhysicalMaterial] : DefaultSound;
        UGameplayStatics::PlaySoundAtLocation(MeshComp, Sound, OutHit.Location);
    }
}

bool UTWStepAnimNotify::LineTrace(const USkeletalMeshComponent* MeshComp, FHitResult& OutHit) const
{
    check(MeshComp);
    check(MeshComp->GetWorld());

    const FVector StartLocation = MeshComp->GetSocketLocation(SocketName);
    const FVector EndLocation = StartLocation + FVector::DownVector * TraceDistance;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(MeshComp->GetOwner());
    Params.bReturnPhysicalMaterial = true;

    return MeshComp->GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, Params);
}
