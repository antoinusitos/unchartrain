// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Interactable.h"
#include "UCT_TrainStopper.generated.h"

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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<AUCT_Train> Train = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_NumberPeopleBoostingUpdate, Category = "UCT")
	int32 NumberPeopleUsing = 0;

public:
	UFUNCTION()
	void OnRep_NumberPeopleBoostingUpdate();

	UFUNCTION(BlueprintCallable)
	void AttachToStopper(ACharacter* character);

	UFUNCTION(BlueprintCallable)
	void DetachToStopper(ACharacter* character);

private:
	TArray<ACharacter*> AllCharactersAttached;
};
