// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Interactable.h"
#include "UCT_Container.generated.h"

class AUCT_Player;

UCLASS()
class UNCHARTRAIN_API AUCT_Container : public AUCT_Interactable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUCT_Container();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
