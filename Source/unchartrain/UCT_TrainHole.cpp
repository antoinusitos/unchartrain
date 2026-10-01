// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_TrainHole.h"
#include "Net/UnrealNetwork.h"

#include "UCT_Player.h"
#include "UCT_TrainHolePlacement.h"

AUCT_TrainHole::AUCT_TrainHole()
{
    bReplicates = true;
}

void AUCT_TrainHole::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    // Call the Super
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUCT_TrainHole, DamageRepaired);
}

void AUCT_TrainHole::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority())
    {
        if (NumberPeopleUsing > 0)
        {
            DamageRepaired += DeltaTime * NumberPeopleUsing;

            if (DamageRepaired >= DamageToReach)
            {
                if (TrainHolePlacement != nullptr)
                {
                    TrainHolePlacement->Used = false;
                }
                Destroy();
            }
        }

        NumberPeopleUsing = 0;
    }
}

void AUCT_TrainHole::OnRep_DamageRepairedUpdate()
{

}

float AUCT_TrainHole::GetCustomSliderValue()
{
    return DamageRepaired / DamageToReach;
}

void AUCT_TrainHole::OnHoldInteraction()    
{
    NumberPeopleUsing = FMath::Clamp(NumberPeopleUsing + 1, 0, NumberPlayersMax);
}