// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SubtitlesContent.generated.h"

/**
 * 
 */
UCLASS()
class HYPERIONCORE_API USubtitlesContent : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Content", meta = (ExposeOnSpawn = true))
		USoundWave* AudioFile;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Details", Meta = (ExposeOnSpawn=true))
		FText Speaker;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Details", Meta = (ExposeOnSpawn=true))
		FString Line;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Content", meta = (ExposeOnSpawn = true))
		float ScreenTime;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings|Colors")
		float BackgroundOpacity = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings|Colors")
		FLinearColor BackgroundColor = FLinearColor(0, 0, 0, BackgroundOpacity);

	void SetDialogue(FString InDialogue);
	void SetSpeaker(FText InSpeaker);
	void SetScreenTime(float InScreenTime);
};
