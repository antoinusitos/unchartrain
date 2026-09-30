// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Item.h"
#include "UCT_ItemCarriable.generated.h"

class AUCT_Player;

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API AUCT_ItemCarriable : public AUCT_Item
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool CanAim = false;
	
	bool IsDirty = true;

public:
	virtual void UseItem(const FVector Loc, const FVector Forward, const AUCT_Player* User);

	virtual void RefillItem();
};
