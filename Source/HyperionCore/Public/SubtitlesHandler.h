// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubtitlesContent.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "SubtitlesHandler.generated.h"

/**
 * 
 */
UCLASS()
class HYPERIONCORE_API USubtitlesHandler : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Settings")
		int ArrayLimit = 3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
		float ScreenTime = 3.5f;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Content")
		FText Subtitle;

	UFUNCTION(BlueprintCallable, Category="Subtitles")
		void ConfigSubtitlesReferences(UVerticalBox* SubtitlesBox, TSubclassOf<USubtitlesContent> SubtitlesContentClass);
	UFUNCTION(BlueprintCallable, Category="Subtitles", meta=(WorldContext="WorldContextObject"))
		static void SubtitlesLogic(const UObject* WorldContextObject, USoundWave* AudioFile, FText InSpeaker, FString InDialogue, float InDuration);
	UFUNCTION(BlueprintCallable, Category="Subtitles", meta=(WorldContext="WorldContextObject"))
		static void PlayAudioWithSubtitles(const UObject* WorldContextObject, USoundWave* Audio, FText Speaker, FString Dialogue, float Duration, float& ReturnValue);
		static void PlayAudio(USoundBase* AudioToPlay);
};
