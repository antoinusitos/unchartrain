// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Interactable.h"
#include "UCT_TrainDirection.generated.h"

class UArrowComponent;
class USpringArmComponent;
class UStaticMeshComponent;

class AUCT_Train;

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API AUCT_TrainDirection : public AUCT_Interactable
{
	GENERATED_BODY()
	
public:
	AUCT_TrainDirection();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UStaticMeshComponent* Lever = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UStaticMeshComponent* Base = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UArrowComponent* PlayerPlacement = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	TWeakObjectPtr<AUCT_Train> Train = nullptr;

	float RotValue = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_RotUpdate, Category = "UCT")
	float Rot = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_IsUsedUpdate, Category = "UCT")
	bool IsUsed = false;

public:
	UFUNCTION()
	void OnRep_RotUpdate();

	UFUNCTION()
	void OnRep_IsUsedUpdate();
};
