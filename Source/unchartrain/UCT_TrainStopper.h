// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Interactable.h"
#include "UCT_TrainStopper.generated.h"

class UArrowComponent;
class USpringArmComponent;
class UStaticMeshComponent;

class AUCT_Train;

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API AUCT_TrainStopper : public AUCT_Interactable
{
	GENERATED_BODY()
	
public:
	AUCT_TrainStopper();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UStaticMeshComponent* Lever = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UStaticMeshComponent* StationBase = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<AUCT_Train> Train = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_TrainCanMoveUpdate, Category = "UCT")
	bool TrainCanMove = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_LockingValueUpdate, Category = "UCT")
	float LockingValue = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReleased = false;

public:
	UFUNCTION()
	void OnRep_LockingValueUpdate();

	UFUNCTION()
	void OnRep_TrainCanMoveUpdate();

	void OnInteract() override;

	void ReceiveMovementInput(float X, float Y) override;

	bool CanUseLongInteraction() override;
};
