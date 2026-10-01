// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_TrainHolePlacement.h"

#include "Components/ArrowComponent.h"

// Sets default values
AUCT_TrainHolePlacement::AUCT_TrainHolePlacement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SocketPlace = CreateDefaultSubobject<UArrowComponent>("SocketPlace");
	SocketPlace->SetupAttachment(RootComponent);
}
