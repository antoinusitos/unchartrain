// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_TrainStopper.h"
#include "Net/UnrealNetwork.h"

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "UCT_Player.h"

AUCT_TrainStopper::AUCT_TrainStopper()
{
    bReplicates = true;

    StationBase = CreateDefaultSubobject<UStaticMeshComponent>("StationBase");
    StationBase->SetupAttachment(Base);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(StationBase);

    Lever = CreateDefaultSubobject<UStaticMeshComponent>("Lever");
    Lever->SetupAttachment(SpringArm);
}

void AUCT_TrainStopper::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority() && IsReleased)
    {
        LockingValue = FMath::Clamp(LockingValue + GetWorld()->GetDeltaSeconds(), 0, 1);
        SpringArm->SetRelativeRotation(FRotator(0, 90, FMath::Lerp(-45.0f, 45.0f, LockingValue)));
        if (LockingValue >= 1 && TrainCanMove)
        {
            TrainCanMove = false;
            IsReleased = false;
        }
    }
}

void AUCT_TrainStopper::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    // Call the Super
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUCT_TrainStopper, NumberPeopleUsing);
    DOREPLIFETIME(AUCT_TrainStopper, TrainCanMove);
}

void AUCT_TrainStopper::OnRep_LockingValueUpdate()
{
    SpringArm->SetRelativeRotation(FRotator(0, 90, FMath::Lerp(-45.0f, 45.0f, LockingValue)));
}

void AUCT_TrainStopper::ReceiveMovementInput(float X, float Y)
{
    if (Y > 0)
    {
        LockingValue = FMath::Clamp(LockingValue - GetWorld()->GetDeltaSeconds(), 0, 1);
        SpringArm->SetRelativeRotation(FRotator(0, 90, FMath::Lerp(-45.0f, 45.0f, LockingValue)));

        if (LockingValue <= 0 && !TrainCanMove)
        {
            TrainCanMove = true;

            for (int32 i = 0; i < AllCharactersAttached.Num(); i++)
            {
                AllCharactersAttached[i]->Client_ExitCurrentStation();
            }
        }
    }
}

void AUCT_TrainStopper::OnInteract()
{
    if (IsReleased || !TrainCanMove)
    {
        return;
    }

    IsReleased = true;
}

bool AUCT_TrainStopper::CanUseLongInteraction()
{
    return !TrainCanMove;
}

void AUCT_TrainStopper::OnRep_TrainCanMoveUpdate()
{

}