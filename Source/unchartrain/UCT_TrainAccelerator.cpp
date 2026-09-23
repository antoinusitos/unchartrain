// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_TrainAccelerator.h"
#include "Net/UnrealNetwork.h"

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

AUCT_TrainAccelerator::AUCT_TrainAccelerator()
{
	bReplicates = true;

    Base = CreateDefaultSubobject<UStaticMeshComponent>("Base");
    RootComponent = Base;

    PlayerPlacement = CreateDefaultSubobject<UArrowComponent>("PlayerPlacement");
    PlayerPlacement->SetupAttachment(Base);
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

void AUCT_TrainAccelerator::OnRep_NumberPeopleUsingUpdate()
{

}

void AUCT_TrainAccelerator::AttachToAccelerator(ACharacter* character)
{
    if (!AllCharactersAttached.Contains(character))
    {
        AllCharactersAttached.Add(character);
        NumberPeopleUsing++;
    }
}

void AUCT_TrainAccelerator::DetachToAccelerator(ACharacter* character)
{
    if (AllCharactersAttached.Contains(character))
    {
        AllCharactersAttached.Remove(character);
        NumberPeopleUsing--;
    }
}