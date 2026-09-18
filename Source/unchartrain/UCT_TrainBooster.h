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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<AUCT_Train> Train = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_NumberPeopleBoostingUpdate, Category = "UCT")
	int32 NumberPeopleBoosting = 0;

public:
	UFUNCTION()
	void OnRep_NumberPeopleBoostingUpdate();

	UFUNCTION(BlueprintCallable)
	void AttachToBooster(ACharacter* character);

	UFUNCTION(BlueprintCallable)
	void DetachToBooster(ACharacter* character);

private:
	TArray<ACharacter*> AllCharactersAttached;
};
