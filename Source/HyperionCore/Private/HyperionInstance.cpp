// Fill out your copyright notice in the Description page of Project Settings.


#include "HyperionInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"

#include "Kismet/KismetSystemLibrary.h"

IOnlineSubsystem* OnlineSubsystem;
FString Self;

UHyperionInstance::UHyperionInstance()
{
	bIsLoggedIn = false;
	bIsSessionLive = false;
	Self = this->GetName();
}

void UHyperionInstance::Init()
{
	Super::Init();
	OnlineSubsystem = IOnlineSubsystem::Get();
	if(GameType == "Online") {
		Login();
	}
}

void UHyperionInstance::Shutdown()
{
	Super::Shutdown();
}

FString UHyperionInstance::GetOnlinePlatformUserName()
{
	if(OnlinePlatformUserName.IsEmpty() || OnlinePlatformUserName == "DummyDisplayName") {
		return UKismetSystemLibrary::GetPlatformUserName();
	} else {
		return OnlinePlatformUserName;
	}
}

void UHyperionInstance::Login()
{
	if (GameType == "Online") {
		if(OnlineSubsystem) {
			if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface()) {
				FOnlineAccountCredentials Credentials;
				Credentials.Id = FString("localhost:6300");
				Credentials.Token = FString("Context_1");
				Credentials.Type = FString("developer");

				Identity->OnLoginCompleteDelegates->AddUObject(this, &UHyperionInstance::OnLoginComplete);
				Identity->Login(0, Credentials);
			}
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("You can't login while the GameType is set to: Singleplayer."));
	}
}

void UHyperionInstance::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
	const FString& Error)
{
	bIsLoggedIn = bWasSuccessful;
	if(OnlineSubsystem){
		UE_LOG(LogTemp, Warning, TEXT("Client successfully logged in. Code: %d"), bWasSuccessful)
		if(IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface()) {
			OnlinePlatformUserName = Identity->GetUserAccount(UserId)->GetDisplayName();
			Identity->ClearOnLoginCompleteDelegates(0, this);
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Client failed to log in. Code: %d"), bWasSuccessful);
	}
}
