// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UCT_TrainHolePlacement.generated.h"

class UArrowComponent;

UCLASS()
class UNCHARTRAIN_API AUCT_TrainHolePlacement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUCT_TrainHolePlacement();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UArrowComponent* SocketPlace = nullptr;

public:
	bool Used = false;

};
