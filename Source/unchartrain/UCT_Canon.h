// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCT_Interactable.h"
#include "UCT_Canon.generated.h"

class UArrowComponent;
class UCameraComponent;
class USpringArmComponent;
class UStaticMeshComponent;

class AUCT_CanonBall;

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API AUCT_Canon : public AUCT_Interactable
{
	GENERATED_BODY()
	
public:
	AUCT_Canon();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UStaticMeshComponent* CanonBase = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UStaticMeshComponent* Cylinder = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UArrowComponent* FirePlace = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UCameraComponent* CameraPlace = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_IsUsedUpdate, Category = "UCT")
	bool IsUsed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_RotXUpdate, Category = "UCT")
	float RotX = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_RotYUpdate, Category = "UCT")
	float RotY = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float MinX = -45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float MaxX = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float MinY = -45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float MaxY = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	float ReloadTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_CurrentReloadTimeUpdate, Category = "UCT")
	float CurrentReloadTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_LoadedUpdate, Category = "UCT")
	bool Loaded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	TSubclassOf<AUCT_CanonBall> CanonBallToSpawn = nullptr;

public:
	UFUNCTION()
	void OnRep_LoadedUpdate();

	UFUNCTION()
	void OnRep_IsUsedUpdate();

	UFUNCTION()
	void OnRep_RotXUpdate();

	UFUNCTION()
	void OnRep_RotYUpdate();

	UFUNCTION()
	void OnRep_CurrentReloadTimeUpdate();

	UFUNCTION(BlueprintCallable)
	void FireCanon();

	UFUNCTION(BlueprintCallable)
	void AddRotation(float X, float Y);

	UFUNCTION(BlueprintCallable)
	void Reloading();
};
