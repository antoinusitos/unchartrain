// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_Train.h"

#include "UCT_TrainAccelerator.h"
#include "UCT_TrainBooster.h"
#include "UCT_TrainBoosterBase.h"
#include "UCT_TrainDirection.h"
#include "UCT_TrainHole.h"
#include "UCT_TrainStopper.h"

#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AUCT_Train::AUCT_Train()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseSceneComponent = CreateDefaultSubobject<USceneComponent>("BaseSceneComponent");
	RootComponent = BaseSceneComponent.Get();

	TrainDirections_Socket = CreateDefaultSubobject<UArrowComponent>("TrainDirection_Socket");
	TrainDirections_Socket->SetupAttachment(RootComponent);

	TrainBooster_Socket = CreateDefaultSubobject<UArrowComponent>("TrainBooster_Socket");
	TrainBooster_Socket->SetupAttachment(RootComponent);

	TrainBoosterBase1_Socket = CreateDefaultSubobject<UArrowComponent>("TrainBoosterBase1_Socket");
	TrainBoosterBase1_Socket->SetupAttachment(RootComponent);

	TrainBoosterBase2_Socket = CreateDefaultSubobject<UArrowComponent>("TrainBoosterBase2_Socket");
	TrainBoosterBase2_Socket->SetupAttachment(RootComponent);

	TrainStopper_Socket = CreateDefaultSubobject<UArrowComponent>("TrainStopper_Socket");
	TrainStopper_Socket->SetupAttachment(RootComponent);

	TrainDamage_Socket = CreateDefaultSubobject<UArrowComponent>("TrainDamage_Socket");
	TrainDamage_Socket->SetupAttachment(RootComponent);

	TrainAccelerator_Socket = CreateDefaultSubobject<UArrowComponent>("TrainAccelerator_Socket");
	TrainAccelerator_Socket->SetupAttachment(RootComponent);
}

void AUCT_Train::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	// Call the Super
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUCT_Train, BoostValue);
	DOREPLIFETIME(AUCT_Train, ReleasingStopping);
}

// Called when the game starts or when spawned
void AUCT_Train::BeginPlay()
{
	Super::BeginPlay();
	
	if (!HasAuthority())
	{
		return;
	}

	if (TrainDirectionToSpawn != nullptr)
	{
		TrainDirection = GetWorld()->SpawnActor<AUCT_TrainDirection>(TrainDirectionToSpawn);
		TrainDirection->AttachToComponent(TrainDirections_Socket, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		TrainDirection->Train = this;
	}

	if (TrainBoosterToSpawn != nullptr)
	{
		TrainBooster = GetWorld()->SpawnActor<AUCT_TrainBooster>(TrainBoosterToSpawn);
		TrainBooster->AttachToComponent(TrainBooster_Socket, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		TrainBooster->Train = this;
	}

	if (TrainBoosterBaseToSpawn != nullptr)
	{
		TrainBoosterBase1 = GetWorld()->SpawnActor<AUCT_TrainBoosterBase>(TrainBoosterBaseToSpawn);
		TrainBoosterBase1->AttachToComponent(TrainBoosterBase1_Socket, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		TrainBoosterBase1->TrainBooster = TrainBooster;

		TrainBoosterBase2 = GetWorld()->SpawnActor<AUCT_TrainBoosterBase>(TrainBoosterBaseToSpawn);
		TrainBoosterBase2->AttachToComponent(TrainBoosterBase2_Socket, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		TrainBoosterBase2->TrainBooster = TrainBooster;

		TrainBooster->BoosterBases.Add(TrainBoosterBase1);
		TrainBooster->BoosterBases.Add(TrainBoosterBase2);

		TrainBoosterBase1->PostSpawn();
		TrainBoosterBase2->PostSpawn();
	}

	if (TrainStopperToSpawn != nullptr)
	{
		TrainStopper = GetWorld()->SpawnActor<AUCT_TrainStopper>(TrainStopperToSpawn);
		TrainStopper->AttachToComponent(TrainStopper_Socket, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		TrainStopper->Train = this;
	}

	if (TrainAcceleratorToSpawn != nullptr)
	{
		TrainAccelerator = GetWorld()->SpawnActor<AUCT_TrainAccelerator>(TrainAcceleratorToSpawn);
		TrainAccelerator->AttachToComponent(TrainAccelerator_Socket, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		TrainAccelerator->Train = this;
	}
}

// Called every frame
void AUCT_Train::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HasAuthority())
	{
		return;
	}

	BoostValue = TrainAccelerator->CurrentProgression >= 100 ? 2 : TrainAccelerator->CurrentProgression >= 0 ? 1 : 0;

	if (TrainStopper->TrainCanMove)
	{
		Speed = FMath::Clamp(Speed + Acceleration * DeltaTime * (TrainAccelerator->CurrentProgression / 100), 0.0f, MaxSpeed * BoostValue);
	}
	else
	{
		Speed = FMath::Clamp(Speed - Acceleration * DeltaTime * 10, 0.0f, MaxSpeed * BoostValue);
	}
	
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * Speed * DeltaTime);

	TrainDirection->Rot = Rotation;

	if (TrainBooster->NumberPeopleBoosting > 0)
	{
		BoostTrain();
	}
	else
	{
		HandleBoost();
	}

	if (TrainStopper->TrainCanMove)
	{
		AddActorWorldRotation(FRotator(0, Rotation, 0));
	}
}

void AUCT_Train::ToggleTrainMovement()
{
	Moving = !Moving;
}

void AUCT_Train::BoostTrain()
{
	Boosted = true;
	BoostValue = FMath::Clamp(BoostValue + TrainBooster->NumberPeopleBoosting * GetWorld()->GetDeltaSeconds() * BoostMultiplier, 1.0f, BoostMax);
	OnBoostValueChange();
}

void AUCT_Train::HandleBoost()
{
	if (BoostValue > 1.0f)
	{
		BoostValue = FMath::Clamp(BoostValue - GetWorld()->GetDeltaSeconds(), 1, BoostMax);
		OnBoostValueChange();
	}
	else
	{
		Boosted = false;
	}
}

void AUCT_Train::TurnLeft()
{
	Rotation = FMath::Clamp(Rotation + TurnSpeed * -1 * GetWorld()->GetDeltaSeconds(), MaxRotation * -1, MaxRotation);
}

void AUCT_Train::TurnRight()
{
	Rotation = FMath::Clamp(Rotation + TurnSpeed * GetWorld()->GetDeltaSeconds(), MaxRotation * -1, MaxRotation);
}

void AUCT_Train::OnRep_BoostValueUpdate()
{
	OnBoostValueChange();
}

void AUCT_Train::OnRep_ReleasingStoppingUpdate()
{

}

void AUCT_Train::TrainTakeDamage()
{
	if (TrainStopperToSpawn != nullptr)
	{
		AUCT_TrainHole* Damage = GetWorld()->SpawnActor<AUCT_TrainHole>(TrainDamageToSpawn);
		Damage->AttachToComponent(TrainDamage_Socket, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}