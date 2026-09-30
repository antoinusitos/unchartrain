// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UCT_ItemCarryingComponent.generated.h"

class AUCT_Weapon;
class AUCT_ItemCarriable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNCHARTRAIN_API UUCT_ItemCarryingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUCT_ItemCarryingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	TSubclassOf<AUCT_Weapon> DebugWeaponToSpawn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_CurrentCarriedItemUpdate, Category = "UCT")
	AUCT_ItemCarriable* CurrentCarriedItem = nullptr;

public:
	void AttachItem(AUCT_ItemCarriable* Item);

	UFUNCTION()
	void OnRep_CurrentCarriedItemUpdate();
};
