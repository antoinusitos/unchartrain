// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_Ladder.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "UCT_Player.h"

AUCT_Ladder::AUCT_Ladder()
{
    TopLocation = CreateDefaultSubobject<UArrowComponent>("TopLocation");
    TopLocation->SetupAttachment(Base);

    TopAttachment = CreateDefaultSubobject<UArrowComponent>("TopAttachment");
    TopAttachment->SetupAttachment(Base);
}

void AUCT_Ladder::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    for (int32 i = 0; i < AllCharactersAttached.Num(); i++)
    {
        FVector Pos = PlayerPlacement->GetComponentLocation();
        Pos.Z = AllCharactersAttached[i]->GetActorLocation().Z;
        AllCharactersAttached[i]->SetActorLocation(Pos, false, nullptr, ETeleportType::ResetPhysics);
    }
}

void AUCT_Ladder::AttachToInteractable(AUCT_Player* character)
{
    Super::AttachToInteractable(character);

    character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

    if (character->GetActorLocation().Z <= PlayerPlacement->GetComponentLocation().Z)
    {
        character->SetActorLocation(PlayerPlacement->GetComponentLocation(), false, nullptr, ETeleportType::ResetPhysics);
    }
    else if (character->GetActorLocation().Z >= TopAttachment->GetComponentLocation().Z)
    {
        character->SetActorLocation(TopAttachment->GetComponentLocation(), false, nullptr, ETeleportType::ResetPhysics);
    }
    else
    {
        FVector Pos = PlayerPlacement->GetComponentLocation();
        Pos.Z = character->GetActorLocation().Z;
        character->SetActorLocation(Pos, false, nullptr, ETeleportType::ResetPhysics);
    }

    character->GetMovementComponent()->Velocity = FVector::ZeroVector;
}

void AUCT_Ladder::DetachToInteractable(AUCT_Player* character)
{
    Super::DetachToInteractable(character);

    character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AUCT_Ladder::ReceiveMovementInput(float X, float Y, AUCT_Player* character)
{
    if (Y < 0)
    {
        character->SetActorLocation(character->GetActorLocation() - FVector::UpVector * GetWorld()->GetDeltaSeconds() * ClimbSpeed, false, nullptr, ETeleportType::ResetPhysics);
        if (character->GetActorLocation().Z <= PlayerPlacement->GetComponentLocation().Z)
        {
            character->Client_ExitCurrentStation();
        }
    }
    else if (Y > 0)
    {
        character->SetActorLocation(character->GetActorLocation() + FVector::UpVector * GetWorld()->GetDeltaSeconds() * ClimbSpeed, false, nullptr, ETeleportType::ResetPhysics);
        if (character->GetActorLocation().Z >= TopLocation->GetComponentLocation().Z)
        {
            character->Client_ExitCurrentStation();
            character->SetActorLocation(TopLocation->GetComponentLocation(), false, nullptr, ETeleportType::TeleportPhysics);
        }
    }
}