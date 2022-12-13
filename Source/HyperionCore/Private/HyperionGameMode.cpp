// Fill out your copyright notice in the Description page of Project Settings.


#include "HyperionGameMode.h"
#include "discord.h"

discord::Core* core{};
discord::Activity activity{};


AHyperionGameMode::AHyperionGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHyperionGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	::core->RunCallbacks();
}

void AHyperionGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AHyperionGameMode::ConnectToDiscord(int clientID)
{
	auto result = discord::Core::Create(clientID, DiscordCreateFlags_NoRequireDiscord, &core);
}

void AHyperionGameMode::UpdateDiscordState(FString State)
{
	const char* state = TCHAR_TO_ANSI(*State);
	activity.SetState(state);
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
}

void AHyperionGameMode::UpdateDiscordDetails(FString Details)
{
	const char* details = TCHAR_TO_ANSI(*Details);
	activity.SetDetails(details);
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
}

