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
	static void ConnectToDiscord(int64 clientID);

	UFUNCTION(BlueprintCallable, Category="Discord")
	static void UpdateDiscordState(FString State);
	UFUNCTION(BlueprintCallable, Category="Discord")
	static void UpdateDiscordDetails(FString Details);
	
};
