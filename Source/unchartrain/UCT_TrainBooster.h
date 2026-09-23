// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Interactable.h"
#include "UCT_TrainBooster.generated.h"

class AUCT_Train;

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API AUCT_TrainBooster : public AUCT_Interactable
{
	GENERATED_BODY()
	
public:
	AUCT_TrainBooster();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<AUCT_Train> Train = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_NumberPeopleBoostingUpdate, Category = "UCT")
	int32 NumberPeopleBoosting = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UCT")
	int32 NumberPeopleMax = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float MinNumber = 60;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float MaxNumber = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float Tolerence = 15.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_PickedNumberUpdate, Category = "UCT")
	int32 PickedNumber = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentValueUpdate, Category = "UCT")
	float CurrentValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float ChangeMultiplier = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float TimeToChangeNumber = 30;

	float CurrentTimeToChangeNumber = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UCT")
	bool IsBoosted = false;

public:
	UFUNCTION()
	void OnRep_NumberPeopleBoostingUpdate();

	UFUNCTION()
	void OnRep_PickedNumberUpdate();

	UFUNCTION()
	void OnRep_CurrentValueUpdate();

	UFUNCTION(BlueprintCallable)
	void AttachToBooster(ACharacter* character);

	UFUNCTION(BlueprintCallable)
	void DetachToBooster(ACharacter* character);

	UFUNCTION(BlueprintCallable)
	void AddPressure();

	UFUNCTION(BlueprintCallable)
	void RemovePressure();

	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeDone();

private:
	TArray<ACharacter*> AllCharactersAttached;
};
