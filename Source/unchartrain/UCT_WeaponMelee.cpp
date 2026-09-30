// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_WeaponMelee.h"

#include "UCT_Player.h"

void AUCT_WeaponMelee::UseItem(const FVector Loc, const FVector Forward, AUCT_Player* User)
{
	User->Attacking = true;

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