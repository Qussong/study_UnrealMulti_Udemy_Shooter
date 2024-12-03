// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/OverheadWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if (nullptr != DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole Role = InPawn->GetLocalRole(); 
	//ENetRole Role = InPawn->GetRemoteRole();
	FString RoleString;
	switch (Role)
	{
	case ENetRole::ROLE_Authority:
		RoleString = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		RoleString = FString("AutonomousProxy");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		RoleString = FString("SimulatedProxy");
		break;
	case ENetRole::ROLE_None:
		RoleString = FString("None");
		break;
	default:
		break;
	}
	FString HUDString = FString::Printf(TEXT("Locale Role :\n%s"), *RoleString);
	//FString HUDString = FString::Printf(TEXT("Remote Role :\n%s"), *RoleString);
	SetDisplayText(HUDString);
}

void UOverheadWidget::NativeConstruct()
{
	RemoveFromParent();
	Super::NativeConstruct();
}
