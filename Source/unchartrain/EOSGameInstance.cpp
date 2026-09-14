// Fill out your copyright notice in the Description page of Project Settings.

#include "EOSGameInstance.h"

#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/OnlineUserCloudInterface.h"

#define SEARCH_KEYWORDS FName(TEXT("SEARCHKEYWORDS"))
#define SEARCH_PRESENCE FName(TEXT("PRESENCESEARCH"))
#define SEARCH_LOBBIES FName(TEXT("LOBBYSEARCH"))

void UEOSGameInstance::Init()
{
	Super::Init();

	OnlineSubsystem = IOnlineSubsystem::Get();

	//TEMP
	/*MenuPlayerController = Cast<ACargoMenuPlayerController>(GetWorld()->GetFirstPlayerController());
	if (MenuPlayerController)
	{
		MenuPlayerController->ShowSessionScreen();
	}*/

	Login();
}

void UEOSGameInstance::Login(FString Token)
{
	if (OnlineSubsystem)
	{
		IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface();
		if (Identity)
		{
			FOnlineAccountCredentials Credentials;
			Credentials.Id = FString("127.0.0.1:8081");
			if (Token == "")
				Credentials.Token = FString("Client1");
			else
				Credentials.Token = Token;
			Credentials.Type = FString("developer");
			Credentials.Type = FString("accountportal");

			Identity->OnLoginCompleteDelegates->AddUObject(this, &UEOSGameInstance::OnLoginComplete);
			Identity->Login(0, Credentials);
		}
	}
}

void UEOSGameInstance::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	UE_LOG(LogTemp, Warning, TEXT("LoggedIn: %d"), bWasSuccessful);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Blue,
			FString::Printf(TEXT("LoggedIn: %d"), bWasSuccessful)
		);
	}

	if (bWasSuccessful)
	{
		connected = true;
		LoginDone();
	}

	if (OnlineSubsystem)
	{
		IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface();
		if (Identity)
		{
			Identity->ClearOnLoginCompleteDelegates(0, this);
		}
	}
}

void  UEOSGameInstance::LoginDone()
{
	UE_LOG(LogTemp, Warning, TEXT("LoginDone"));
	/*MenuPlayerController = Cast<ACargoMenuPlayerController>(GetWorld()->GetFirstPlayerController());
	if (MenuPlayerController)
	{
		MenuPlayerController->ShowMenuScreen();
	}*/
}

void UEOSGameInstance::CreateSession(const FString& SessionNameToCreate)
{
	CreatedSessionName = SessionNameToCreate;
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface();
		if (SessionPtr)
		{
			/*if (MenuPlayerController)
			{
				MenuPlayerController->SetSessionText("Creating a Session...");
			}*/

			FOnlineSessionSettings SessionSettings;

			SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UEOSGameInstance::OnCreateSessionComplete);
			SessionPtr->OnSessionUserInviteAcceptedDelegates.AddUObject(this, &UEOSGameInstance::OnSessionUserInviteAccepted);

			SessionSettings.bIsLANMatch = false;
			SessionSettings.NumPublicConnections = 7;
			SessionSettings.bAllowJoinInProgress = true;
			SessionSettings.bAllowJoinViaPresence = true;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bUsesPresence = true;
			SessionSettings.bUseLobbiesIfAvailable = true;

			SessionSettings.Set(SEARCH_KEYWORDS, SessionNameToCreate, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
			const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			SessionPtr->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), FName(CreatedSessionName), SessionSettings);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session : not logged in"));
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString::Printf(TEXT("Cannot create session : not logged in"))
			);
		}
	}
}

void UEOSGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Create Session Success: %d"), bWasSuccessful);

	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Blue,
				FString::Printf(TEXT("Created session: %s"), *SessionName.ToString())
			);
		}

		/*if (MenuPlayerController)
		{
			MenuPlayerController->SetSessionText("Looking for a player to duel...");
		}*/

		UWorld* World = GetWorld();
		if (World)
		{

			World->ServerTravel(FString("/Game/AssetsV2/Maps/LobbyV2?listen"));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("Failed to create session!"))
			);
		}
	}

	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface();
		if (SessionPtr)
		{
			SessionPtr->ClearOnCreateSessionCompleteDelegates(this);
		}
	}
}

void UEOSGameInstance::FindSessions(const FString& LobbyNameToFind)
{
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface();
		if (SessionPtr)
		{
			/*if (MenuPlayerController)
			{
				MenuPlayerController->SetSessionText("Looking for a Session...");
			}*/

			SearchSettings = MakeShareable(new FOnlineSessionSearch());
			SearchSettings->MaxSearchResults = 10000;
			SearchSettings->bIsLanQuery = false;
			SearchSettings->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
			SearchSettings->QuerySettings.Set(SEARCH_KEYWORDS, LobbyNameToFind, EOnlineComparisonOp::Equals);
			SearchSettings->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);

			SessionPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UEOSGameInstance::OnFindSessionComplete);

			const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			SessionPtr->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SearchSettings.ToSharedRef());
		}
	}
}

void UEOSGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Find Session Success : %d"), bWasSuccessful);

	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found %d Lobbies"), SearchSettings->SearchResults.Num());

		if (SearchSettings->SearchResults.Num() == 0)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					15.f,
					FColor::Red,
					FString::Printf(TEXT("No Session found"))
				);
			}
			/*if (MenuPlayerController)
			{
				MenuPlayerController->SetSessionText("No Session found");
			}*/

			return;
		}

		if (OnlineSubsystem)
		{
			IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface();
			if (SessionPtr)
			{
				for (auto Result : SearchSettings->SearchResults)
				{
					FString Id = Result.GetSessionIdStr();
					FString User = Result.Session.OwningUserName;
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(
							-1,
							15.f,
							FColor::Cyan,
							FString::Printf(TEXT("Id: %s, User: %s"), *Id, *User)
						);
					}
					/*if (MenuPlayerController)
					{
						MenuPlayerController->SetSessionText("Found a Session, Joining...");
					}*/

					SessionPtr->OnJoinSessionCompleteDelegates.AddUObject(this, &UEOSGameInstance::OnJoinSessionComplete);

					const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
					SessionPtr->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), FName("Test Session"), Result);
					return;
				}
			}
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString::Printf(TEXT("Find Session Success %d"), bWasSuccessful)
			);
		}
		if (connected)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					15.f,
					FColor::Red,
					FString::Printf(TEXT("No Session found"))
				);
			}
			/*if (MenuPlayerController)
			{
				MenuPlayerController->SetSessionText("No Session found");
			}*/
		}
	}

	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface();
		if (SessionPtr)
		{
			SessionPtr->ClearOnFindSessionsCompleteDelegates(this);
		}
	}
}

void UEOSGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("Join Session Success : %d"), Result == EOnJoinSessionCompleteResult::Success);

	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface();
		if (SessionPtr)
		{
			FString ConnectionInfo = FString();
			SessionPtr->GetResolvedConnectString(FName("Test Session"), ConnectionInfo);
			if (!ConnectionInfo.IsEmpty())
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(
						-1,
						15.f,
						FColor::Yellow,
						FString::Printf(TEXT("Connect string: %s"), *ConnectionInfo)
					);
				}
				APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				if (PC)
				{
					UE_LOG(LogTemp, Warning, TEXT("Traveling to... %s"), *ConnectionInfo);
					PC->ClientTravel(ConnectionInfo, ETravelType::TRAVEL_Absolute);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("CANNOT JOIN"));
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(
						-1,
						15.f,
						FColor::Red,
						FString::Printf(TEXT("CANNOT JOIN"))
					);
				}
			}
		}
	}
}

void UEOSGameInstance::OnSessionUserInviteAccepted(const bool bWasSuccessful, const int32 ControllerId, FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult& InviteResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnSessionUserInviteAccepted Success : %d"), bWasSuccessful);
}

const bool UEOSGameInstance::GetIsConnected() const
{
	return connected;
}