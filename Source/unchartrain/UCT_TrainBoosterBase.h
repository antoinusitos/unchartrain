// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Interactable.h"
#include "UCT_TrainBoosterBase.generated.h"

class AUCT_TrainBooster;

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API AUCT_TrainBoosterBase : public AUCT_Interactable
{
	GENERATED_BODY()
	
public:
	AUCT_TrainBoosterBase(); 

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_TrainBoosterUpdate, Category = "UCT")
	TWeakObjectPtr<AUCT_TrainBooster> TrainBooster = nullptr;

public:
	UFUNCTION()
	void OnRep_TrainBoosterUpdate();

	UFUNCTION(BlueprintCallable)
	void PostSpawn();

	UFUNCTION(BlueprintCallable)
	void AttachToBooster(ACharacter* character);

	UFUNCTION(BlueprintCallable)
	void DetachToBooster(ACharacter* character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeDone(float CurrentValue, int32 PickedNumber, float Tolerence);
};
