// Fill out your copyright notice in the Description page of Project Settings.


#include "HyperionHUD.h"
#include "Engine/Canvas.h"

void AHyperionHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrosshair(Canvas->SizeX, Canvas->SizeY);
}

void AHyperionHUD::DrawCrosshair(int X, int Y)
{
	DrawRect(FLinearColor(255, 255, 255), X/2, Y/2, 2, 2);
}
