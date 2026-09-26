// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Interactable.h"
#include "UCT_TrainAccelerator.generated.h"

class UArrowComponent;
class USpringArmComponent;
class USpringArmComponent;

class AUCT_Train;

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API AUCT_TrainAccelerator : public AUCT_Interactable
{
	GENERATED_BODY()
	
public:
	AUCT_TrainAccelerator();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UStaticMeshComponent* StationBase = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_CurrentProgressionUpdate, Category = "UCT")
	float CurrentProgression = 0.0f; // from 0 to 100 (included)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	TWeakObjectPtr<AUCT_Train> Train = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	int32 Direction1 = 0; //Player 1 dir ON SERVER ONLY

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	int32 Direction2 = 0; //Player 2 dir ON SERVER ONLY

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UCT")
	float FillingSpeed = 20;

public:
	UFUNCTION()
	void OnRep_CurrentProgressionUpdate();

	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeDone();
}; 
