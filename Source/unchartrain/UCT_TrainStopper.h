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
	UStaticMeshComponent* Base = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UArrowComponent* PlayerPlacement = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<AUCT_Train> Train = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_NumberPeopleBoostingUpdate, Category = "UCT")
	int32 NumberPeopleUsing = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TrainCanMove = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_LockingValueUpdate, Category = "UCT")
	float LockingValue = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReleased = false;

public:
	UFUNCTION()
	void OnRep_NumberPeopleBoostingUpdate();

	UFUNCTION()
	void OnRep_LockingValueUpdate();

	UFUNCTION(BlueprintCallable)
	void AttachToStopper(ACharacter* character);

	UFUNCTION(BlueprintCallable)
	void DetachToStopper(ACharacter* character);

	UFUNCTION(BlueprintCallable)
	void UnlockTrain();

	UFUNCTION(BlueprintCallable)
	void ReleaseStopper();

private:
	TArray<ACharacter*> AllCharactersAttached;
};
