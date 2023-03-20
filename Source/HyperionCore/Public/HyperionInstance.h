// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HyperionInstance.generated.h"

/**
 * 
 */
UCLASS()
class HYPERIONCORE_API UHyperionInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    UHyperionInstance();
	virtual void Init() override;
	virtual void Shutdown() override;
};
