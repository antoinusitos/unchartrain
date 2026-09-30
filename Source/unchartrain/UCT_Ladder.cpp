// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_Ladder.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "UCT_Player.h"

void AUCT_Ladder::AttachToInteractable(AUCT_Player* character)
{
    Super::AttachToInteractable(character);

    character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
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
        character->SetActorLocation(character->GetActorLocation() - FVector::UpVector * GetWorld()->GetDeltaSeconds() * ClimbSpeed, false, nullptr, ETeleportType::TeleportPhysics);
        if (character->GetActorLocation().Z <= PlayerPlacement->GetComponentLocation().Z)
        {
            character->Client_ExitCurrentStation();
        }
    }
    else if (Y > 0)
    {
        character->SetActorLocation(character->GetActorLocation() + FVector::UpVector * GetWorld()->GetDeltaSeconds() * ClimbSpeed, false, nullptr, ETeleportType::TeleportPhysics);
    }
}