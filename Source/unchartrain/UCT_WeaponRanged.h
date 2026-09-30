// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Weapon.h"
#include "UCT_WeaponRanged.generated.h"

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API AUCT_WeaponRanged : public AUCT_Weapon
{
	GENERATED_BODY()

public:
	AUCT_WeaponRanged();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_CurrentAmmoUpdate, Category = "UCT")
	int32 CurrentAmmo = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	int32 AmmoMax = 5;

public:
	virtual void UseItem(const FVector Loc, const FVector Forward, const AUCT_Player* User) override;

	UFUNCTION()
	void OnRep_CurrentAmmoUpdate();

	virtual void RefillItem() override;
	
};
