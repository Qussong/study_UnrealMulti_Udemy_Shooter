// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"

ALobbyGameMode::ALobbyGameMode()
{
	bUseSeamlessTravel = true;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (HasAuthority())
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		if (NumberOfPlayers == 2)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				// D:/Unreal Project/study_UnrealMulti_Udemy_Shooter/Blaster/Content/_Blaster/Maps/BlasterMap.umap
				World->ServerTravel(FString("/Game/_Blaster/Maps/BlasterMap?listen"));
			}
		}
	}
}
