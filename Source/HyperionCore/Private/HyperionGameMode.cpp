// Fill out your copyright notice in the Description page of Project Settings.


#include "HyperionGameMode.h"
#include "discord.h"

discord::Core* core{};
auto result = discord::Core::Create(1052232496722497556, DiscordCreateFlags_NoRequireDiscord, &core);

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
//	ConnectToDiscord();
	discord::Activity Activity{};
	Activity.GetTimestamps();
	UpdateDiscordDetails("Cortex Island");
	UpdateDiscordState("Exploring");
}

/*void AHyperionGameMode::ConnectToDiscord()
{
	auto result = discord::Core::Create(1052232496722497556, DiscordCreateFlags_NoRequireDiscord, &core);
}*/

void AHyperionGameMode::UpdateDiscordState(FString State)
{
	const char* state = TCHAR_TO_ANSI(*State);
	discord::Activity Activity{};
	Activity.SetState(state);
	core->ActivityManager().UpdateActivity(Activity, [](discord::Result result) {});
}

void AHyperionGameMode::UpdateDiscordDetails(FString Details)
{
	const char* details = TCHAR_TO_ANSI(*Details);
	discord::Activity Activity{};
	Activity.SetDetails(details);
	core->ActivityManager().UpdateActivity(Activity, [](discord::Result result) {});
}

