// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_TrainBooster.h"
#include "Net/UnrealNetwork.h"

AUCT_TrainBooster::AUCT_TrainBooster()
{
    bReplicates = true;
}

void AUCT_TrainBooster::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    // Call the Super
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUCT_TrainBooster, NumberPeopleBoosting);
}

void AUCT_TrainBooster::OnRep_NumberPeopleBoostingUpdate()
{

}

void AUCT_TrainBooster::AttachToBooster(ACharacter* character)
{
    if (!AllCharactersAttached.Contains(character))
    {
        AllCharactersAttached.Add(character);
        NumberPeopleBoosting++;
    }
}

void AUCT_TrainBooster::DetachToBooster(ACharacter* character)
{
    if (AllCharactersAttached.Contains(character))
    {
        AllCharactersAttached.Remove(character);
        NumberPeopleBoosting--;
    }
}