// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UCT_CanonBall.generated.h"

UCLASS()
class UNCHARTRAIN_API AUCT_CanonBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUCT_CanonBall();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Dir;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Damage = 30;
};
