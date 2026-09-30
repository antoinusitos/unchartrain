// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Container.h"
#include "UCT_AmmoContainer.generated.h"

class AUCT_Player;

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API AUCT_AmmoContainer : public AUCT_Container
{
	GENERATED_BODY()

public:
	void OnQuickUse(AUCT_Player* Player) override;
	
};
