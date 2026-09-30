// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_ItemCarryingComponent.h"
#include "Net/UnrealNetwork.h"

#include "UCT_Player.h"
#include "UCT_WeaponRanged.h"

// Sets default values for this component's properties
UUCT_ItemCarryingComponent::UUCT_ItemCarryingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

void UUCT_ItemCarryingComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	// Call the Super
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UUCT_ItemCarryingComponent, CurrentCarriedItem);
}

// Called when the game starts
void UUCT_ItemCarryingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	if (DebugWeaponToSpawn != nullptr)
	{
		AUCT_WeaponRanged* RangedWeapon = GetWorld()->SpawnActor<AUCT_WeaponRanged>(DebugWeaponToSpawn);
		AttachItem(RangedWeapon);
	}
}

void UUCT_ItemCarryingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UUCT_ItemCarryingComponent::AttachItem(AUCT_ItemCarriable* Item)
{
	CurrentCarriedItem = Item;
	CurrentCarriedItem->AttachToComponent(Cast<AUCT_Player>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "HandGrip_R");
}

void UUCT_ItemCarryingComponent::OnRep_CurrentCarriedItemUpdate()
{

}