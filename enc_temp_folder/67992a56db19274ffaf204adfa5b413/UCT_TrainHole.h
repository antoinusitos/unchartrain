// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Interactable.h"
#include "UCT_TrainHole.generated.h"

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API AUCT_TrainHole : public AUCT_Interactable
{
	GENERATED_BODY()

public:
	AUCT_TrainHole();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_NumberPeopleUsingUpdate, Category = "UCT")
	int32 NumberPeopleUsing = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_DamageRepairedUpdate, Category = "UCT")
	float DamageRepaired = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float DamageToReach = 10;

public:
	UFUNCTION()
	void OnRep_NumberPeopleUsingUpdate();

	UFUNCTION()
	void OnRep_DamageRepairedUpdate();
};
