// Fill out your copyright notice in the Description page of Project Settings.


#include "HardwareDetails.h"
#include "HardwareInfo.h"

FString UHardwareDetails::GetCPUBrand()
{
	return FPlatformMisc::GetCPUBrand();
}

FString UHardwareDetails::GetGPUBrand()
{
	return FPlatformMisc::GetPrimaryGPUBrand();
}

FString UHardwareDetails::GetRHI()
{
	return FHardwareInfo::GetHardwareInfo(NAME_RHI);
}

int32 UHardwareDetails::GetCPUCores()
{
	return FPlatformMisc::NumberOfCores();
}

int32 UHardwareDetails::GetCPUThreads()
{
	if(PLATFORM_WINDOWS)
	{
		return FWindowsPlatformMisc::NumberOfCoresIncludingHyperthreads();
	}
}

int32 UHardwareDetails::GetRAMCapacity()
{
	return FGenericPlatformMemory::GetPhysicalGBRam();
}

FString UHardwareDetails::GetOSVersion()
{
	return FPlatformMisc::GetOSVersion();
}
