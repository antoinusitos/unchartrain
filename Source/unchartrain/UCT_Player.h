// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UCT_Player.generated.h"

class UCameraComponent;
class USpringArmComponent;

class AUCT_Interactable;
class UUCT_ItemCarryingComponent;

UCLASS()
class UNCHARTRAIN_API AUCT_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUCT_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void LookAround(float Value);

	void LookUp(float Value);

	void Interaction();
	void StopInteraction();
	void TickInteraction();

	void CheckFrontForHint();

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "UCT")
	void Server_AttachToInteraction(AUCT_Interactable* Interactable);

	void Server_AttachToInteraction_Implementation(AUCT_Interactable* Interactable);

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "UCT")
	void Server_DetachToInteraction(AUCT_Interactable* Interactable);

	void Server_DetachToInteraction_Implementation(AUCT_Interactable* Interactable);

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "UCT")
	void Server_UseReloadOnInteraction(AUCT_Interactable* Interactable);

	void Server_UseReloadOnInteraction_Implementation(AUCT_Interactable* Interactable);

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "UCT")
	void Server_UseInteraction(AUCT_Interactable* Interactable);

	void Server_UseInteraction_Implementation(AUCT_Interactable* Interactable);

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "UCT")
	void Server_SendMouseDeltaToInteraction(AUCT_Interactable* Interactable, float X, float Y);

	void Server_SendMouseDeltaToInteraction_Implementation(AUCT_Interactable* Interactable, float X, float Y);

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "UCT")
	void Server_SendMovementDeltaToInteraction(AUCT_Interactable* Interactable, float X, float Y);

	void Server_SendMovementDeltaToInteraction_Implementation(AUCT_Interactable* Interactable, float X, float Y);

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "UCT")
	void Server_OnInteract(AUCT_Interactable* Interactable);

	void Server_OnInteract_Implementation(AUCT_Interactable* Interactable);

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "UCT")
	void Server_QuickUse(AUCT_Interactable* Interactable);

	void Server_QuickUse_Implementation(AUCT_Interactable* Interactable);

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "UCT")
	void Server_UseCarriedItem(const FVector Loc, const FVector Forward, const AUCT_Player* User);

	void Server_UseCarriedItem_Implementation(const FVector Loc, const FVector Forward, const AUCT_Player* User);

	UFUNCTION(Reliable, Client, BlueprintCallable, Category = "UCT")
	void Client_ExitCurrentStation();

	void Client_ExitCurrentStation_Implementation();

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "UCT")
	void Server_HoldOnInteraction(AUCT_Interactable* Interactable);

	void Server_HoldOnInteraction_Implementation(AUCT_Interactable* Interactable);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowHint(const FString& Text);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowLongInputSlider(bool State, float Value);

	void Reload();
	void StopReload();

	void CheckReloading();

	void Fire();
	
	void Aim();
	void StopAim();

	void CheckCarriedState();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCarriedUI();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthUI();

	UFUNCTION()
	void OnRep_CurrentHealthUpdate();

	void PlayerTakeDamage(float Amount);

	UFUNCTION()
	void OnRep_AimingUpdate();

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "UCT")
	void Server_Aim(bool NewState);

	void Server_Aim_Implementation(bool NewState);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UUCT_ItemCarryingComponent* ItemCarryingComponent = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float InteractionRange = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float LongInteractionStartTime = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float LongInteractionTime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_CurrentHealthUpdate, Category = "UCT")
	float CurrentHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_AimingUpdate, Category = "UCT")
	bool Aiming = false;

private:
	float CameraRotation = 0.0f;

	AUCT_Interactable* CurrentInteractableUsed = nullptr;
	AUCT_Interactable* CurrentFacedInteractable = nullptr;

	bool Reloading = false;

	APlayerController* LocalController = nullptr;

	float LastMouseXDelta = 0.0f;
	float LastMouseYDelta = 0.0f;

	float LastMovementXDelta = 0.0f;
	float LastMovementYDelta = 0.0f;

	float InteractTime = 0;
	bool Interacting = false;
};
