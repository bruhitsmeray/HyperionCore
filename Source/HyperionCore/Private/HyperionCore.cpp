// Copyright Epic Games, Inc. All Rights Reserved.

#include "HyperionCore.h"

#define LOCTEXT_NAMESPACE "FHyperionCoreModule"

DEFINE_LOG_CATEGORY_STATIC(LogHyperionCore, All, All);

#define LOG(LogString)	UE_LOG(LogHyperionCore, Display, TEXT("%s"), *FString(LogString));
#define LOG_WARNING(LogString)	UE_LOG(LogHyperionCore, Warning, TEXT("%s"), *FString(LogString));
#define LOG_ERROR(LogString)	UE_LOG(LogHyperionCore, Error, TEXT("%s"), *FString(LogString));

void FHyperionCoreModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	LOG("Initializing HyperionCore.");
}

void FHyperionCoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	LOG("Shutting down HyperionCore.");
}

#undef LOG
#undef LOG_WARNING
#undef LOG_ERROR
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHyperionCoreModule, HyperionCore)