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
};
