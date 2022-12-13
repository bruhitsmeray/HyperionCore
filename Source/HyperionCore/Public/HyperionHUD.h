// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HyperionHUD.generated.h"

/**
 * 
 */
UCLASS()
class HYPERIONCORE_API AHyperionHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void DrawHUD() override;
	UFUNCTION(BlueprintCallable, Category = "HUD")
		void DrawCrosshair(int X, int Y);
};
