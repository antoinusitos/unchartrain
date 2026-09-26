// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_Interactable.h"
#include "Net/UnrealNetwork.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AUCT_Interactable::AUCT_Interactable()
{
	bReplicates = true;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Base = CreateDefaultSubobject<USceneComponent>("Base");
	RootComponent = Base;

	PlayerPlacement = CreateDefaultSubobject<UArrowComponent>("PlayerPlacement");
	PlayerPlacement->SetupAttachment(Base);

	CameraPlacement = CreateDefaultSubobject<UCameraComponent>("CameraPlacement");
	CameraPlacement->SetupAttachment(Base);

}

// Called when the game starts or when spawned
void AUCT_Interactable::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUCT_Interactable::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	// Call the Super
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUCT_Interactable, NumberPeopleUsing);
}

// Called every frame
void AUCT_Interactable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUCT_Interactable::UseInteractable()
{

}

void AUCT_Interactable::AttachToInteractable(ACharacter* character)
{
	if (!AllCharactersAttached.Contains(character))
	{
		AllCharactersAttached.Add(character);
		NumberPeopleUsing++;
	}
}

void AUCT_Interactable::DetachToInteractable(ACharacter* character)
{
	if (AllCharactersAttached.Contains(character))
	{
		AllCharactersAttached.Remove(character);
		NumberPeopleUsing--;
	}
}

void AUCT_Interactable::OnRep_NumberPeopleUsingUpdate()
{

}

FVector AUCT_Interactable::GetPlayerPlacementPosition() const
{
	return PlayerPlacement->GetComponentLocation();
}

FRotator AUCT_Interactable::GetPlayerPlacementRotation() const
{
	return PlayerPlacement->GetComponentRotation();
}

void AUCT_Interactable::UseReloadInteraction()
{

}

void AUCT_Interactable::ReceiveMouseInput(float X, float Y)
{
	
}