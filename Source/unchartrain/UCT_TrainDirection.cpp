// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_TrainDirection.h"
#include "Net/UnrealNetwork.h"

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "UCT_Train.h"

AUCT_TrainDirection::AUCT_TrainDirection()
{
    bReplicates = true;

    StationBase = CreateDefaultSubobject<UStaticMeshComponent>("StationBase");
    StationBase->SetupAttachment(Base);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(StationBase);

    Lever = CreateDefaultSubobject<UStaticMeshComponent>("Lever");
    Lever->SetupAttachment(SpringArm);

    ShouldReceiveMovementInput = true;
}

void AUCT_TrainDirection::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    // Call the Super
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUCT_TrainDirection, Rot);
    DOREPLIFETIME(AUCT_TrainDirection, IsUsed);
}

void AUCT_TrainDirection::Tick(float DeltaTime)
{
    if (HasAuthority())
    {
        SpringArm->SetRelativeRotation(FRotator(0, 0, Rot * RotValue));
    }
}

void AUCT_TrainDirection::OnRep_RotUpdate()
{
    SpringArm->SetRelativeRotation(FRotator(0, 0, Rot * RotValue));
}

void AUCT_TrainDirection::OnRep_IsUsedUpdate()
{
    
}

void AUCT_TrainDirection::ReceiveMovementInput(float X, float Y)
{
    if (X < 0)
    {
        Train->TurnLeft();
    }
    else if (X > 0)
    {
        Train->TurnRight();
    }
}