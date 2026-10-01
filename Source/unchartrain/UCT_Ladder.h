// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Interactable.h"
#include "UCT_Ladder.generated.h"

class UArrowComponent;

class AUCT_Player;

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API AUCT_Ladder : public AUCT_Interactable
{
	GENERATED_BODY()
	
public:
	AUCT_Ladder();

	virtual void Tick(float DeltaTime) override;

public:
	void ReceiveMovementInput(float X, float Y, AUCT_Player* character) override;

	virtual void AttachToInteractable(AUCT_Player* character) override;

	virtual void DetachToInteractable(AUCT_Player* character) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UArrowComponent* TopLocation = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UArrowComponent* TopAttachment = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float ClimbSpeed = 4.0f;
};
