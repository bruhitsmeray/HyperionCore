// Fill out your copyright notice in the Description page of Project Settings.


#include "SubtitlesHandler.h"

UVerticalBox* SubtitlesBoxReference = nullptr;
TSubclassOf<USubtitlesContent> SubtitlesContentReference;
USubtitlesContent* SubtitlesContent;
int ArrayLimitReference;


void USubtitlesHandler::NativeConstruct()
{
	Super::NativeConstruct();
	ArrayLimitReference = ArrayLimit;
}

void USubtitlesHandler::ConfigSubtitlesReferences(UVerticalBox* SubtitlesBox, TSubclassOf<USubtitlesContent> SubtitlesContentClass)
{
	SubtitlesBoxReference = SubtitlesBox;
	SubtitlesContentReference = SubtitlesContentClass;
}

void USubtitlesHandler::SubtitlesLogic(const UObject* WorldContextObject, USoundWave* AudioFile, FText InSpeaker, FString InDialogue, float InDuration)
{
	if(!InDialogue.IsEmpty() && IsValid(SubtitlesBoxReference))
	{
		UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
		if(SubtitlesBoxReference->GetChildrenCount() >= ArrayLimitReference && IsValid(SubtitlesBoxReference->GetChildAt(0)))
		{
			SubtitlesBoxReference->GetChildAt(0)->RemoveFromParent();
		}
		
		if(IsValid(World) && IsValid(SubtitlesBoxReference)) {
			SubtitlesContent = CreateWidget<USubtitlesContent>(World, SubtitlesContentReference);
			SubtitlesContent->SetSpeaker(InSpeaker);
			SubtitlesContent->SetDialogue(InDialogue);
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



void USubtitlesHandler::PlayAudioWithSubtitles(const UObject* WorldContextObject, USoundWave* Audio, FText Speaker, FString Dialogue, float Duration, float& ReturnValue)
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
	SubtitlesLogic(WorldContextObject, Audio, Speaker, Dialogue, Duration);
	ReturnValue = Duration;
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
