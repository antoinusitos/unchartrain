// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_TrainStopper.h"
#include "Net/UnrealNetwork.h"

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

AUCT_TrainStopper::AUCT_TrainStopper()
{
    bReplicates = true;

    Base = CreateDefaultSubobject<UStaticMeshComponent>("Base");
    RootComponent = Base;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(Base);

    Lever = CreateDefaultSubobject<UStaticMeshComponent>("Lever");
    Lever->SetupAttachment(SpringArm);

    PlayerPlacement = CreateDefaultSubobject<UArrowComponent>("PlayerPlacement");
    PlayerPlacement->SetupAttachment(Base);
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
}

void AUCT_TrainStopper::OnRep_NumberPeopleBoostingUpdate()
{

}

void AUCT_TrainStopper::OnRep_LockingValueUpdate()
{
    SpringArm->SetRelativeRotation(FRotator(0, 90, FMath::Lerp(-45.0f, 45.0f, LockingValue)));
}

void AUCT_TrainStopper::AttachToStopper(ACharacter* character)
{
    if (!AllCharactersAttached.Contains(character))
    {
        AllCharactersAttached.Add(character);
        NumberPeopleUsing++;
    }
}

void AUCT_TrainStopper::DetachToStopper(ACharacter* character)
{
    if (AllCharactersAttached.Contains(character))
    {
        AllCharactersAttached.Remove(character);
        NumberPeopleUsing--;
    }
}

void AUCT_TrainStopper::UnlockTrain()
{
    LockingValue = FMath::Clamp(LockingValue - GetWorld()->GetDeltaSeconds(), 0, 1);
    SpringArm->SetRelativeRotation(FRotator(0, 90, FMath::Lerp(-45.0f, 45.0f, LockingValue)));

    if (LockingValue <= 0 && !TrainCanMove)
    {
        TrainCanMove = true;
    }
}

void AUCT_TrainStopper::ReleaseStopper()
{
    if (IsReleased || !TrainCanMove)
    {
        return;
    }

    IsReleased = true;
}