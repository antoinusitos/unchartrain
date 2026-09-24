// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UCT_Player.generated.h"

class UCameraComponent;
class USpringArmComponent;

class AUCT_Interactable;

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

public:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void LookAround(float Value);

	void LookUp(float Value);

	void Interaction();

	void CheckFrontForHint();

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "UCT")
	void Server_AttachToInteraction(AUCT_Interactable* Interactable);

	void Server_AttachToInteraction_Implementation(AUCT_Interactable* Interactable);

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "UCT")
	void Server_DetachToInteraction(AUCT_Interactable* Interactable);

	void Server_DetachToInteraction_Implementation(AUCT_Interactable* Interactable);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowHint(const FString& Text);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UCameraComponent* CameraComponent = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float InteractionRange = 200.0f;

private:
	float CameraRotation = 0.0f;

	TWeakObjectPtr<AUCT_Interactable> CurrentInteractableUsed = nullptr;
};
