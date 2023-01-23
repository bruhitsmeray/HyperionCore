// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"
#include "HyperionInstance.generated.h"

/**
 * 
 */
UCLASS()
class HYPERIONCORE_API UHyperionInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    UHyperionInstance();
	virtual void Init() override;
	virtual void Shutdown() override;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Preferences", meta = (GetOptions = "GameTypeList"))
		FString GameType = "Offline";
	UFUNCTION(BlueprintCallable, Category="Preferences")
		TArray<FString> GameTypeList() const {
			return {
				"Offline",
				"Online"
			};
	};
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Online|Status")
		bool bIsLoggedIn;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Online|Status")
		bool bIsSessionLive;
	UFUNCTION(BlueprintCallable, Category="Online|Info")
		FString GetOnlinePlatformUserName();
		FString OnlinePlatformUserName;

public:
	UFUNCTION(Exec, BlueprintCallable, Category="Online|Login")
		void Login();
		void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
};
