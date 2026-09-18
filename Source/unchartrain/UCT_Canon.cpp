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

    Base = CreateDefaultSubobject<UStaticMeshComponent>("Base");
    RootComponent = Base;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(Base);

    Cylinder = CreateDefaultSubobject<UStaticMeshComponent>("Cylinder");
    Cylinder->SetupAttachment(SpringArm);

    PlayerPlacement = CreateDefaultSubobject<UArrowComponent>("PlayerPlacement");
    PlayerPlacement->SetupAttachment(Base);

    FirePlace = CreateDefaultSubobject<UArrowComponent>("FirePlace");
    FirePlace->SetupAttachment(Cylinder);

    CameraPlace = CreateDefaultSubobject<UCameraComponent>("CameraPlace");
    CameraPlace->SetupAttachment(SpringArm);
}

void AUCT_Canon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    // Call the Super
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUCT_Canon, IsUsed);
    DOREPLIFETIME(AUCT_Canon, RotX);
    DOREPLIFETIME(AUCT_Canon, RotY);
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

void AUCT_Canon::FireCanon()
{
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

void AUCT_Canon::AddRotation(float X, float Y)
{
    RotX = FMath::Clamp(RotX + X, MinX, MaxX);
    RotY = FMath::Clamp(RotY + Y, MinY, MaxY);
}