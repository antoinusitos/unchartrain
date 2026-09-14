// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "EOSGameInstance.generated.h"

class IOnlineSubsystem;
class FOnlineSessionSearch;

/**
 * 
 */
UCLASS()
class UNCHARTRAIN_API UEOSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void Login(FString Token = "");

	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	UFUNCTION(BlueprintCallable)
	void CreateSession(const FString& SessionNameToCreate);

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void FindSessions(const FString& LobbyNameToFind);
	TSharedPtr<FOnlineSessionSearch> SearchSettings;

	void OnFindSessionComplete(bool bWasSuccessful);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void OnSessionUserInviteAccepted(const bool bWasSuccessful, const int32 ControllerId, FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult& InviteResult);

	UFUNCTION(BlueprintCallable, Category = "CardGame")
	const bool GetIsConnected() const;

	void LoginDone();

protected:
	IOnlineSubsystem* OnlineSubsystem = nullptr;

	//ACargoMenuPlayerController* MenuPlayerController = nullptr;

	bool connected = false;

public:
	FString CreatedSessionName = "";
};
