// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsSubsystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem()
	: CreateSessionCompleteDelegate(
		  FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete))
	  , FindSessionsCompleteDelegate(
		  FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionComplete))
	  , JoinSessionCompleteDelegate(
		  FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete))
	  , DestroySessionCompleteDelegate(
		  FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete))
	  , StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete))
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}
}

void UMultiplayerSessionsSubsystem::CreateSession(int32 NumPublicConnections, FString MatchType)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}

	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (nullptr != ExistingSession)
	{
		SessionInterface->DestroySession(NAME_GameSession);
	}

	// Store the delegate in a FDelegateHandle so we can later remove it from the delegate list
	CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	LastSessionSettings= MakeShareable(new FOnlineSessionSettings());
	{
		LastSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
		LastSessionSettings->NumPublicConnections = NumPublicConnections;
		LastSessionSettings->bAllowJoinInProgress = true;
		LastSessionSettings->bAllowJoinViaPresence = true;
		LastSessionSettings->bShouldAdvertise = true;
		LastSessionSettings->bUsesPresence = true;
		LastSessionSettings->bUseLobbiesIfAvailable = true;
		LastSessionSettings->Set(FName("MatchType")
								 , FString("FreeForAll")
								 , EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	}

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	bool bCreateSession = SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings); 
	if (false == bCreateSession)
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

		// Broadcast our own custom delegate
		MultiplayerOnCreateSessionComplete.Broadcast(false);
	}
}

void UMultiplayerSessionsSubsystem::FindSession(int32 MaxSearchResults)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}
}

void UMultiplayerSessionsSubsystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}
}

void UMultiplayerSessionsSubsystem::DestroySession()
{
	if (!SessionInterface.IsValid())
	{
		return;
	}
}

void UMultiplayerSessionsSubsystem::StartSession()
{
	if (!SessionInterface.IsValid())
	{
		return;
	}
}

void UMultiplayerSessionsSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (SessionInterface.IsValid())
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	}

	MultiplayerOnCreateSessionComplete.Broadcast(bWasSuccessful);
}

void UMultiplayerSessionsSubsystem::OnFindSessionComplete(bool bWasSuccessful)
{
}

void UMultiplayerSessionsSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

void UMultiplayerSessionsSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void UMultiplayerSessionsSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
}
