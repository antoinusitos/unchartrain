// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UCT_Train.generated.h"

class AUCT_TrainDirection;
class AUCT_TrainBooster;

class UArrowComponent;
class USceneComponent;

UCLASS()
class UNCHARTRAIN_API AUCT_Train : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUCT_Train();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	AUCT_TrainDirection* TrainDirection = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	AUCT_TrainBooster* TrainBooster = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	TWeakObjectPtr<USceneComponent> BaseSceneComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	TSubclassOf<AUCT_TrainDirection> TrainDirectionToSpawn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UArrowComponent* TrainDirections_Socket = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	TSubclassOf<AUCT_TrainBooster> TrainBoosterToSpawn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UArrowComponent* TrainBooster_Socket = nullptr;

	float Speed = 0.0f;
	float MaxSpeed = 400.0f;
	float Acceleration = 100.0f;
	float Break = 100.0f;
	float TurnSpeed = 0.3f;
	float MaxRotation = 0.2f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UCT")
	float BoostMax = 7.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float BoostMultiplier = 1.5f;

	// Runtime
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_BoostValueUpdate, Category = "UCT")
	float BoostValue = 1.0f;
	float Rotation = 0.0f;

	bool Moving = false;
	bool Boosted = false;

public:
	UFUNCTION(BlueprintCallable)
	void ToggleTrainMovement();

	UFUNCTION(BlueprintCallable)
	void BoostTrain();

	UFUNCTION(BlueprintCallable)
	void HandleBoost();

	UFUNCTION(BlueprintCallable)
	void TurnLeft();

	UFUNCTION(BlueprintCallable)
	void TurnRight();

	UFUNCTION()
	void OnRep_BoostValueUpdate();

	UFUNCTION(BlueprintImplementableEvent)
	void OnBoostValueChange();
};
