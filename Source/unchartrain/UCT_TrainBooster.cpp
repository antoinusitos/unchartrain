// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_TrainBooster.h"
#include "Net/UnrealNetwork.h"

AUCT_TrainBooster::AUCT_TrainBooster()
{
    bReplicates = true;

}

void AUCT_TrainBooster::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        PickedNumber = FMath::RandRange(0, 100);
        OnChangeDone();
    }
}

void AUCT_TrainBooster::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    // Call the Super
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUCT_TrainBooster, NumberPeopleBoosting);
    DOREPLIFETIME(AUCT_TrainBooster, PickedNumber);
    DOREPLIFETIME(AUCT_TrainBooster, CurrentValue);
}

void AUCT_TrainBooster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UE_LOG(LogTemp, Warning, TEXT("Tick %f"), TimeToChangeNumber);

    if (HasAuthority())
    {
        TimeToChangeNumber -= DeltaTime;
        UE_LOG(LogTemp, Warning, TEXT("TimeToChangeNumber %f"), TimeToChangeNumber);
        if (TimeToChangeNumber <= 0)
        {
            TimeToChangeNumber = 10;
            PickedNumber = FMath::RandRange(0, 100);
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
    CurrentValue = FMath::Clamp(CurrentValue + GetWorld()->GetDeltaSeconds() * ChangeMultiplier, 0.0f, 100.0f);

    if (CurrentValue <= PickedNumber + 5 && CurrentValue >= PickedNumber - 5)
    {
        UE_LOG(LogTemp, Warning, TEXT("BOOST"));
        IsBoosted = true;
    }
    else
    {
        IsBoosted = false;
    }
}

void AUCT_TrainBooster::RemovePressure()
{
    CurrentValue = FMath::Clamp(CurrentValue - GetWorld()->GetDeltaSeconds() * ChangeMultiplier, 0.0f, 100.0f);

    if (CurrentValue <= PickedNumber + 5 && CurrentValue >= PickedNumber - 5)
    {
        UE_LOG(LogTemp, Warning, TEXT("BOOST"));
        IsBoosted = true;
    }
    else
    {
        IsBoosted = false;
    }
}