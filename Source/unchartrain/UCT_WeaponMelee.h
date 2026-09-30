// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Weapon.h"
#include "UCT_WeaponMelee.generated.h"

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API AUCT_WeaponMelee : public AUCT_Weapon
{
	GENERATED_BODY()
	
public:
	virtual void UseItem(const FVector Loc, const FVector Forward, AUCT_Player* User) override;
};
