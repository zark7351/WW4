// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionMenu.h"
#include "Components/Button.h"
#include "WW4/Online/WW4OnlineSessionSubsystem.h"
#include "WW4/Common/WW4CommonFunctionLibrary.h"
#include "Components/ScrollBox.h"

void USessionMenu::NativeConstruct()
{
	Super::NativeConstruct();
	HostButton->OnClicked.AddDynamic(this, &USessionMenu::OnHostButtonClick);
	JoinButton->OnClicked.AddDynamic(this, &USessionMenu::OnJoinButtonClick);
	Init();
}

void USessionMenu::OnHostButtonClick()
{
	UWW4CommonFunctionLibrary::PrintCommonMessage(FString(TEXT("HostBtnClicked")));
	HostButton->SetIsEnabled(false);
	if (Subsystem)
	{
		Subsystem->CreateSession(NumPublicConnections, GameType);
	}
}

void USessionMenu::OnJoinButtonClick()
{
	JoinButton->SetIsEnabled(false);
	if (Subsystem)
	{
		Subsystem->FindSessions(10000);
	}
}

void USessionMenu::Init()
{
	PathToLobby = FString::Printf(TEXT("%s?Listen"), *PathToLobby);
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->bShowMouseCursor = true;
		}
	}
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		Subsystem = GameInstance->GetSubsystem<UWW4OnlineSessionSubsystem>();
	}
	if (Subsystem)
	{
		Subsystem->WW4CreateSessionComplateDelegate.AddDynamic(this, &USessionMenu::OnCreateSession);
		Subsystem->WW4FindSessionCompleteDelegate.AddUObject(this, &USessionMenu::OnFindSession);
		Subsystem->WW4JoinSessionCompleteDelegate.AddUObject(this, &USessionMenu::OnJoinSession);
	}
}

void USessionMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UWW4CommonFunctionLibrary::PrintCommonMessage(FString(TEXT("Create session seccess!")));
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(PathToLobby);
		}
	}
	else
	{
		UWW4CommonFunctionLibrary::PrintCommonMessage(FString(TEXT("Create session fail!")),FColor::Red);
		HostButton->SetIsEnabled(true);
	}
}

void USessionMenu::OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	UWW4CommonFunctionLibrary::PrintCommonMessage(FString::Printf(TEXT("%d Success, %d"), SessionResults.Num(), bWasSuccessful), FColor::Red);
	if (!Subsystem)
	{
		return;
	}
	if (!bWasSuccessful || SessionResults.Num()<=0)
	{
		JoinButton->SetIsEnabled(true);
	}
	else
	{
		SessionList->ClearChildren();

		for (auto Result : SessionResults)
		{
			if (SessionItemClass)
			{
				UUserWidget* Item = CreateWidget<UUserWidget>(GetWorld(), SessionItemClass);
				SessionList->AddChild(Item);
			}

			//FString SettingValue;
			//Result.Session.SessionSettings.Get(FName("GameType"), SettingValue);
			//if (SettingValue == GameType)
			//{
			//	Subsystem->JoinSession(Result);
			//	return;
			//}
		}
	}
}

void USessionMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FString Address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);
			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(
						-1,
						15.f,
						FColor::Purple,
						FString::Printf(TEXT("%s"), *Address)
					);
				}
				PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
	}
	if (Result!=EOnJoinSessionCompleteResult::Success)
	{
		JoinButton->SetIsEnabled(true);
	}
}
