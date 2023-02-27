// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperionGameMode.h"

AHyperionGameMode::AHyperionGameMode() {
	PrimaryActorTick.bCanEverTick = true;
}

void AHyperionGameMode::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

void AHyperionGameMode::BeginPlay() {
	Super::BeginPlay();
}
