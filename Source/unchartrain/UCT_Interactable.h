// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UCT_Interactable.generated.h"

class UArrowComponent; 
class USceneComponent;

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
	virtual void Execute();

	UFUNCTION(BlueprintCallable)
	void AttachToInteractable(ACharacter* character);

	UFUNCTION(BlueprintCallable)
	void DetachToInteractable(ACharacter* character);

	UFUNCTION()
	void OnRep_NumberPeopleUsingUpdate();

	FVector GetPlayerPlacementPosition() const;

	FRotator GetPlayerPlacementRotation() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	UArrowComponent* PlayerPlacement = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	USceneComponent* Base = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_NumberPeopleUsingUpdate, Category = "UCT")
	int32 NumberPeopleUsing = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	int32 NumberPlayersMax = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool PlayerNeedAttachTo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	bool ReplacePlayerWhenAttached = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UCT")
	TArray<ACharacter*> AllCharactersAttached;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCT")
	FString Hint = "";
};
