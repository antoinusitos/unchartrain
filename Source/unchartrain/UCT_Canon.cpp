// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_Canon.h"
#include "Net/UnrealNetwork.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "UCT_CanonBall.h"

AUCT_Canon::AUCT_Canon()
{
    bReplicates = true;

    CanonBase = CreateDefaultSubobject<UStaticMeshComponent>("CanonBase");
    CanonBase->SetupAttachment(Base);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(CanonBase);

    Cylinder = CreateDefaultSubobject<UStaticMeshComponent>("Cylinder");
    Cylinder->SetupAttachment(SpringArm);

    FirePlace = CreateDefaultSubobject<UArrowComponent>("FirePlace");
    FirePlace->SetupAttachment(Cylinder);

    CameraPlacement->SetupAttachment(SpringArm);
}

void AUCT_Canon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    // Call the Super
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUCT_Canon, IsUsed);
    DOREPLIFETIME(AUCT_Canon, RotX);
    DOREPLIFETIME(AUCT_Canon, RotY);
    DOREPLIFETIME(AUCT_Canon, Loaded);
    DOREPLIFETIME(AUCT_Canon, CurrentReloadTime);
}

void AUCT_Canon::Tick(float DeltaTime)
{
    if (HasAuthority())
    {
        SpringArm->SetRelativeRotation(FRotator(RotY, RotX, 0.0f));
    }
}

void AUCT_Canon::OnRep_IsUsedUpdate()
{

}

void AUCT_Canon::UseInteractable()
{
    if (!Loaded)
    {
        return;
    }

    Loaded = false;

    AUCT_CanonBall* CanonBall = GetWorld()->SpawnActor<AUCT_CanonBall>(CanonBallToSpawn, FTransform(FirePlace->GetComponentLocation()));

    if (CanonBall)
    {
        CanonBall->Dir = FirePlace->GetForwardVector();
    }
}

void AUCT_Canon::OnRep_RotXUpdate()
{
    SpringArm->SetRelativeRotation(FRotator(RotY, RotX, 0.0f));
}

void AUCT_Canon::OnRep_RotYUpdate()
{
    SpringArm->SetRelativeRotation(FRotator(RotY, RotX, 0.0f));
}

void AUCT_Canon::OnRep_LoadedUpdate()
{

}

void AUCT_Canon::UseReloadInteraction()
{
    if (Loaded)
    {
        return;
    }

    CurrentReloadTime += GetWorld()->GetDeltaSeconds();
    if (CurrentReloadTime >= ReloadTime)
    {
        CurrentReloadTime = 0;
        Loaded = true;
    }
}

void AUCT_Canon::OnRep_CurrentReloadTimeUpdate()
{

}

void AUCT_Canon::AttachToInteractable(ACharacter* character)
{
    Super::AttachToInteractable(character);

    if (AllCharactersAttached.Contains(character))
    {
        IsUsed = true;
    }
}

void AUCT_Canon::DetachToInteractable(ACharacter* character)
{
    Super::DetachToInteractable(character);

    if (AllCharactersAttached.Num() == 0)
    {
        IsUsed = false;
    }
}

void AUCT_Canon::ReceiveMouseInput(float X, float Y)
{
    RotX = FMath::Clamp(RotX + X, MinX, MaxX);
    RotY = FMath::Clamp(RotY + Y, MinY, MaxY);
}