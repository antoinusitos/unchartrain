// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_TrainStopper.h"
#include "Net/UnrealNetwork.h"

AUCT_TrainStopper::AUCT_TrainStopper()
{
    bReplicates = true;
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

