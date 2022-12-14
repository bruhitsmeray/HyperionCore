// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HyperionGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HYPERIONCORE_API AHyperionGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AHyperionGameMode();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category="Discord")
	static void ConnectToDiscord(const int64 clientID, const bool bRequireDiscordToRun);

	UFUNCTION(BlueprintCallable, Category="Discord")
	static void SetDiscordState(FString State);
	UFUNCTION(BlueprintCallable, Category="Discord")
	static void SetDiscordDetails(FString Details);
	UFUNCTION(BlueprintCallable, Category="Discord")
	static void StartDiscordTimer();
	UFUNCTION(BlueprintCallable, Category="Discord")
	static void UpdateDiscordActivity();
};
