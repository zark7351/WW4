// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "SessionMenu.generated.h"

/**
 * 
 */

class UButton;

UCLASS()
class WW4_API USessionMenu : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UScrollBox* SessionList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> SessionItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumPublicConnections{2};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString GameType{ TEXT("PVP") };

protected:

	 virtual void NativeConstruct() override;

	 UFUNCTION()
	 void OnHostButtonClick();

	 UFUNCTION()
	 void OnJoinButtonClick();

	 void Init();

	 UFUNCTION()
	 void OnCreateSession(bool bWasSuccessful);

	 //UFUNCTION()
	 void OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);

	 //UFUNCTION()
	 void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);

private:

	class UWW4OnlineSessionSubsystem* Subsystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PathToLobby{ TEXT("") };
};
