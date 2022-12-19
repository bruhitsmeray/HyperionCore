// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperionGameMode.h"
#include "discord.h"

discord::Core* core{};
discord::Activity activity{};

AHyperionGameMode::AHyperionGameMode() {
	PrimaryActorTick.bCanEverTick = true;
}

void AHyperionGameMode::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if(core) {
		::core->RunCallbacks();
	}
}

void AHyperionGameMode::BeginPlay() {
	Super::BeginPlay();
}

void AHyperionGameMode::ConnectToDiscord(int64 clientID, bool bRequireDiscordToRun) {
	auto result = discord::Core::Create(clientID, bRequireDiscordToRun ? DiscordCreateFlags_Default : DiscordCreateFlags_NoRequireDiscord, &core);
	StartDiscordTimer();
}

void AHyperionGameMode::DisconnectFromDiscord()
{
	if(core) {
		activity.SetState("");
		activity.SetDetails("");
		EndDiscordTimer();
		
		delete core;
		core = nullptr;
	}
}

void AHyperionGameMode::SetDiscordState(FString State) {
	const char* state = TCHAR_TO_UTF8(*State);
	activity.SetState(state);
	UpdateDiscordActivity();
}

void AHyperionGameMode::SetDiscordDetails(FString Details) {
	const char* details = TCHAR_TO_UTF8(*Details);
	activity.SetDetails(details);
	UpdateDiscordActivity();
}

void AHyperionGameMode::StartDiscordTimer() {
	activity.GetTimestamps().SetStart((FDateTime::UtcNow().ToUnixTimestamp()));
	activity.GetTimestamps().SetEnd(0);
	UpdateDiscordActivity();
}

void AHyperionGameMode::EndDiscordTimer()
{
	activity.GetTimestamps().SetEnd((FDateTime::UtcNow().ToUnixTimestamp()));
	UpdateDiscordActivity();
}

void AHyperionGameMode::UpdateDiscordActivity() {
	if(core) {
		core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
	}
}

