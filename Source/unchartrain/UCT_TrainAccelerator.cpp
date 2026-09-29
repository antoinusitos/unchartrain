// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_TrainAccelerator.h"
#include "Net/UnrealNetwork.h"

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

AUCT_TrainAccelerator::AUCT_TrainAccelerator()
{
	bReplicates = true;

    StationBase = CreateDefaultSubobject<UStaticMeshComponent>("StationBase");
    StationBase->SetupAttachment(Base);
}

void AUCT_TrainAccelerator::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	// Call the Super
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUCT_TrainAccelerator, CurrentProgression);
	DOREPLIFETIME(AUCT_TrainAccelerator, NumberPeopleUsing);
}

void AUCT_TrainAccelerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		CurrentProgression = FMath::Clamp(CurrentProgression + (Direction1 + Direction2) * DeltaTime * FillingSpeed, 0.0f, 100.0f);
        OnChangeDone();
	}
}

void AUCT_TrainAccelerator::OnRep_CurrentProgressionUpdate()
{
    OnChangeDone();
}

void AUCT_TrainAccelerator::ReceiveMovementInput(float X, float Y, AUCT_Player* character)
{
	for (int32 i = 0; i < AllCharactersAttached.Num(); i++)
	{
		if (AllCharactersAttached[i] == character)
		{
			if (i + 1 == 1)
			{
				Direction1 = X < 0 ? -1 : X > 0 ? 1 : 0;
			}
			else if (i + 1 == 2)
			{
				Direction2 = X < 0 ? -1 : X > 0 ? 1 : 0;
			}
		}
	}
}