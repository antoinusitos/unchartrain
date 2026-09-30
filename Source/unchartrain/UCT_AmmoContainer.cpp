// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_AmmoContainer.h"

#include "UCT_Player.h"
#include "UCT_ItemCarriable.h"
#include "UCT_ItemCarryingComponent.h"

void AUCT_AmmoContainer::OnQuickUse(AUCT_Player* Player)
{
	if (Player->ItemCarryingComponent == nullptr || Player->ItemCarryingComponent->CurrentCarriedItem == nullptr)
	{
		return;
	}

	Player->ItemCarryingComponent->CurrentCarriedItem->RefillItem();
}