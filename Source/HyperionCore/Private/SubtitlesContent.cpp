// Fill out your copyright notice in the Description page of Project Settings.


#include "SubtitlesContent.h"

void USubtitlesContent::SetDialogue(FString InDialogue)
{
	Line = InDialogue;
}

void USubtitlesContent::SetSpeaker(FText InSpeaker)
{
	Speaker = InSpeaker;
}

void USubtitlesContent::SetLineColor(FLinearColor InLineColor)
{
	LineColor = InLineColor;
}

void USubtitlesContent::SetScreenTime(float InScreenTime)
{
	ScreenTime = InScreenTime;
}
