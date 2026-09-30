// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UCT_Interactable.generated.h"

class UArrowComponent;
class UCameraComponent;
class USceneComponent;

class AUCT_Player;

UCLASS()
class UNCHARTRAIN_API AUCT_Interactable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUCT_Interactable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void AttachToInteractable(AUCT_Player* character);

	UFUNCTION(BlueprintCallable)
	virtual void DetachToInteractable(AUCT_Player* character);

	virtual void UseInteractable();

	virtual void OnInteract();

	virtual void ReceiveMouseInput(float X, float Y);

	virtual void ReceiveMovementInput(float X, float Y, AUCT_Player* character);

	UFUNCTION()
	void OnRep_NumberPeopleUsingUpdate();

	FVector GetPlayerPlacementPosition() const;

	FRotator GetPlayerPlacementRotation() const;

	virtual void UseReloadInteraction();

	virtual void OnLongInteraction(AUCT_Player* Player);

	virtual void OnQuickUse(AUCT_Player* Player);

	virtual void OnHoldInteraction();

	virtual bool CanUseLongInteraction();

	virtual float GetCustomSliderValue();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UArrowComponent* PlayerPlacement = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	USceneComponent* Base = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UCameraComponent* CameraPlacement = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_NumberPeopleUsingUpdate, Category = "UCT")
	int32 NumberPeopleUsing = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	int32 NumberPlayersMax = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool PlayerNeedAttachTo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool PlayerNeedAttachToLongInteraction = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool ReplacePlayerWhenAttached = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool ReplaceCameraWhenAttachedLongInteraction = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool ReplaceCameraWhenAttached = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool ShouldReceiveMouseInput = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool ShouldReceiveMovementInput = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool ShouldReceiveZeroMovementInput = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool ShouldLockCamera = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool AttachWithLongInteraction = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool UseLongInteraction = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool UseSimpleInteraction = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool HoldInteraction = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool UseCustomSliderValue = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool CanQuickUse = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UCT")
	TArray<AUCT_Player*> AllCharactersAttached;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MultiLine = "true"), Category = "UCT")
	FText Hint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MultiLine = "true"), Category = "UCT")
	FText UsingInstructions;
};
