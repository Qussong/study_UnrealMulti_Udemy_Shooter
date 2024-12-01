// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BlasterPlayerController.h"

ABlasterPlayerController::ABlasterPlayerController()
{
	bReplicates = true;
}

void ABlasterPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ABlasterPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABlasterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

