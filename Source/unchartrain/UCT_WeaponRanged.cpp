// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_WeaponRanged.h"
#include "Net/UnrealNetwork.h"

#include "UCT_Player.h"

void AUCT_WeaponRanged::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    // Call the Super
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUCT_WeaponRanged, CurrentAmmo);
}

void AUCT_WeaponRanged::UseItem(const FVector Loc, const FVector Forward, AUCT_Player* User)
{
	if (CurrentAmmo > 0)
	{
		CurrentAmmo--;
		IsDirty = true;

		FVector Start = Loc;
		FVector End = Loc + Forward * HitRange;
		FHitResult Result;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(User);

		if (GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECollisionChannel::ECC_Camera, Params))
		{
			if (Result.GetActor()->IsA(AUCT_Player::StaticClass()))
			{
				AUCT_Player* Player = Cast<AUCT_Player>(Result.GetActor());
				Player->PlayerTakeDamage(Damage);
			}
		}
	}
}

void AUCT_WeaponRanged::OnRep_CurrentAmmoUpdate()
{
	IsDirty = true;
}

void AUCT_WeaponRanged::RefillItem()
{
	CurrentAmmo = AmmoMax;
	IsDirty = true;
}