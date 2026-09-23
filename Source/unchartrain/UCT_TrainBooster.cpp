// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_TrainBooster.h"
#include "Net/UnrealNetwork.h"

#include "UCT_TrainBoosterBase.h"

AUCT_TrainBooster::AUCT_TrainBooster()
{
    bReplicates = true;

}

void AUCT_TrainBooster::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        CurrentTimeToChangeNumber = FMath::RandRange(TimeToChangeNumberMin, TimeToChangeNumberMax);
        PickedNumber = FMath::RandRange(MinNumber, MaxNumber);
    }

    CurrentValue = MinNumber;

    OnChangeDone();
}

void AUCT_TrainBooster::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    // Call the Super
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUCT_TrainBooster, NumberPeopleBoosting);
    DOREPLIFETIME(AUCT_TrainBooster, PickedNumber);
    DOREPLIFETIME(AUCT_TrainBooster, CurrentValue);
    DOREPLIFETIME(AUCT_TrainBooster, BoosterBases);
}

void AUCT_TrainBooster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority())
    {
        CurrentTimeToChangeNumber -= DeltaTime;
        if (CurrentTimeToChangeNumber <= 0)
        {
            CurrentTimeToChangeNumber = FMath::RandRange(TimeToChangeNumberMin, TimeToChangeNumberMax);
            PickedNumber = FMath::RandRange(MinNumber, MaxNumber);
            OnChangeDone();
        }
    }
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

void AUCT_TrainBooster::OnRep_PickedNumberUpdate()
{
    OnChangeDone();
}

void AUCT_TrainBooster::OnRep_CurrentValueUpdate()
{
    OnChangeDone();
}

void AUCT_TrainBooster::AddPressure()
{
    CurrentValue = FMath::Clamp(CurrentValue + GetWorld()->GetDeltaSeconds() * ChangeMultiplier, MinNumber, MaxNumber);
    OnChangeDone();

    if (CurrentValue <= PickedNumber + (Tolerence / 2) && CurrentValue >= PickedNumber - (Tolerence / 2))
    {
        IsBoosted = true;
    }
    else
    {
        IsBoosted = false;
    }
}

void AUCT_TrainBooster::RemovePressure()
{
    CurrentValue = FMath::Clamp(CurrentValue - GetWorld()->GetDeltaSeconds() * ChangeMultiplier, MinNumber, MaxNumber);
    OnChangeDone();

    if (CurrentValue <= PickedNumber + (Tolerence / 2) && CurrentValue >= PickedNumber - (Tolerence / 2))
    {
        IsBoosted = true;
    }
    else
    {
        IsBoosted = false;
    }
}

void AUCT_TrainBooster::OnChangeDone()
{
    for (int32 i = 0; i < BoosterBases.Num(); i++)
    {
        if (BoosterBases[i] != nullptr)
        {
            BoosterBases[i]->OnChangeDone(CurrentValue, PickedNumber, Tolerence);
        }
    }
}

void AUCT_TrainBooster::OnRep_BoosterBasesUpdate()
{
    OnChangeDone();
}