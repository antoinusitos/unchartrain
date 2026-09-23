// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_TrainBoosterBase.h"
#include "Net/UnrealNetwork.h"

#include "UCT_TrainBooster.h"

AUCT_TrainBoosterBase::AUCT_TrainBoosterBase()
{
    bReplicates = true;
}

void AUCT_TrainBoosterBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    // Call the Super
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUCT_TrainBoosterBase, TrainBooster);
}

void AUCT_TrainBoosterBase::AttachToBooster(ACharacter* character)
{
    TrainBooster->AttachToBooster(character);
}

void AUCT_TrainBoosterBase::DetachToBooster(ACharacter* character)
{
    TrainBooster->DetachToBooster(character);
}

void AUCT_TrainBoosterBase::PostSpawn()
{
    OnChangeDone(TrainBooster->CurrentValue, TrainBooster->PickedNumber, TrainBooster->Tolerence);
}

void AUCT_TrainBoosterBase::OnRep_TrainBoosterUpdate()
{
    PostSpawn();
}