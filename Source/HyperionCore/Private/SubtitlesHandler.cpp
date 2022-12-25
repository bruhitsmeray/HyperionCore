// Fill out your copyright notice in the Description page of Project Settings.


#include "SubtitlesHandler.h"

UVerticalBox* SubtitlesBoxReference = nullptr;
TSubclassOf<USubtitlesContent> SubtitlesContentReference;
USubtitlesContent* SubtitlesContent;

void USubtitlesHandler::ConfigSubtitlesReferences(UVerticalBox* SubtitlesBox, TSubclassOf<USubtitlesContent> SubtitlesContentClass)
{
	SubtitlesBoxReference = SubtitlesBox;
	SubtitlesContentReference = SubtitlesContentClass;
}

void USubtitlesHandler::SubtitlesLogic(USoundWave* AudioFile, FText InSpeaker, FString InDialogue, FLinearColor InColor, float InDuration)
{
	if(!InDialogue.IsEmpty() && IsValid(SubtitlesBoxReference))
	{
		UWorld* World = GEngine->GameViewport->GetWorld();
		if(SubtitlesBoxReference->GetChildrenCount() >= 3 && IsValid(SubtitlesBoxReference->GetChildAt(0)))
		{
			SubtitlesBoxReference->GetChildAt(0)->RemoveFromParent();
		}
		
		if(IsValid(World) && IsValid(SubtitlesBoxReference)) {
			SubtitlesContent = CreateWidget<USubtitlesContent>(World, SubtitlesContentReference);
			SubtitlesContent->SetSpeaker(InSpeaker);
			SubtitlesContent->SetDialogue(InDialogue);
			SubtitlesContent->SetLineColor(InColor);
			SubtitlesContent->SetScreenTime(InDuration);
			SubtitlesContent->SetRenderTransformAngle(180);
			SubtitlesBoxReference->AddChildToVerticalBox(SubtitlesContent);
			
			if(AudioFile) {
				PlayAudio(AudioFile);
				UE_LOG(LogTemp, Display, TEXT("Playing audio: %s with a duration of: %f."), *AudioFile->GetName(), AudioFile->Duration);
			}
		}
	}
}

void USubtitlesHandler::PlayAudio(USoundBase* AudioToPlay)
{
	if(AudioToPlay)
	{
		FSlateSound NewAudio;
		NewAudio.SetResourceObject(AudioToPlay);
		FSlateApplication::Get().PlaySound(NewAudio);
	}
}

void USubtitlesHandler::PlayAudioWithSubtitles(USoundWave* Audio, FText Speaker, FString Dialogue, FLinearColor Color, float Duration, float& ReturnValue)
{
	if(IsValid(Audio))
	{
		if(Dialogue.IsEmpty() && !Audio->Subtitles.GetData()->Text.IsEmpty())
		{
			Dialogue = Audio->Subtitles.GetData()->Text.ToString();
		}

		if(Duration == 0)
		{
			Duration = Audio->Duration;
		}
	}
	SubtitlesLogic(Audio, Speaker, Dialogue, Color, Duration);
	ReturnValue = Duration;
}

