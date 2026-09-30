// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_ItemCarriable.h"
#include "UCT_Weapon.generated.h"

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API AUCT_Weapon : public AUCT_ItemCarriable
{
	GENERATED_BODY()

public:
	AUCT_Weapon();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	int32 Damage = 5;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	int32 HitRange = 200;
};
