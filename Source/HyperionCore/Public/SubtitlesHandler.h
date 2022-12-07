// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SubtitlesHandler.generated.h"

/**
 * 
 */
UCLASS()
class HYPERIONCORE_API USubtitlesHandler : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Settings")
		int ArrayLimit = 3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
		float ScreenTime = 3.5f;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Content")
		FText Subtitle;
};
