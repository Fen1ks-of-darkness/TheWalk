// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Animations/TWPawnAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "Core/Helpers/TWHelperFunctions.h"

void UTWPawnAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    Pawn = TryGetPawnOwner();
    if (Pawn)
    {
        Movement = FTWHelperFunctions::GetComponentByInterface<ITWMovement>(Pawn);
    }
}

void UTWPawnAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (Pawn)
    {
        Speed = Pawn->GetVelocity().Size();
        Direction = UKismetAnimationLibrary::CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());

        AController* Controller = Pawn->GetController();
        const FRotator ActorRotation = Pawn->GetActorRotation();
        if (Controller)
        {
            const FRotator ControllerRotation = Controller->GetControlRotation();
            const FRotator DeltaRotator = (ControllerRotation - ActorRotation).GetNormalized();

            Yaw = DeltaRotator.Yaw;
            Pitch = DeltaRotator.Pitch;
        }

        if (Movement)
        {
            bIsFalling = Movement->IsInAir();
            bIsCroucing = Movement->IsCrouch();
        }
    }
}
