// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_CanonBall.h"

// Sets default values
AUCT_CanonBall::AUCT_CanonBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void AUCT_CanonBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		SetActorLocation(GetActorLocation() + Dir * Speed);
	}
}

