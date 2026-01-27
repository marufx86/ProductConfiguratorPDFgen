// Simple Export Library Implementation

#include "SimpleExportLibrary.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/DateTime.h"
#include "HAL/PlatformFileManager.h"

void USimpleExportLibrary::ExportStringToJSON(
	const FString& JsonContent,
	const FString& FileName,
	bool& Success,
	FString& FilePath)
{
	Success = false;

	// Build file path
	FString SaveDir = FPaths::ProjectSavedDir() / TEXT("Configurations");
	FString FullFileName = FileName.IsEmpty() 
		? FString::Printf(TEXT("Config_%s.json"), *GetTimestamp())
		: FString::Printf(TEXT("%s.json"), *FileName);
	
	FilePath = SaveDir / FullFileName;

	// Ensure directory exists
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.DirectoryExists(*SaveDir))
	{
		if (!PlatformFile.CreateDirectoryTree(*SaveDir))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create directory: %s"), *SaveDir);
			return;
		}
	}

	// Save to file
	if (FFileHelper::SaveStringToFile(JsonContent, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		Success = true;
		UE_LOG(LogTemp, Log, TEXT("Configuration exported to: %s"), *FilePath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save file: %s"), *FilePath);
	}
}

FString USimpleExportLibrary::GetTimestamp()
{
	FDateTime Now = FDateTime::Now();
	return FString::Printf(TEXT("%04d-%02d-%02d_%02d-%02d-%02d"),
		Now.GetYear(), Now.GetMonth(), Now.GetDay(),
		Now.GetHour(), Now.GetMinute(), Now.GetSecond());
}

FString USimpleExportLibrary::BuildConfigJSON(
	const FString& ConfigName,
	const FString& Timestamp,
	const TArray<FString>& Variants,
	const FString& Environment,
	const FString& Camera)
{
	// Build JSON manually (simple and reliable)
	FString Json = TEXT("{\n");
	Json += FString::Printf(TEXT("  \"ConfigurationName\": \"%s\",\n"), *ConfigName);
	Json += FString::Printf(TEXT("  \"Timestamp\": \"%s\",\n"), *Timestamp);
	
	// Variants array
	Json += TEXT("  \"SelectedVariants\": [\n");
	for (int32 i = 0; i < Variants.Num(); i++)
	{
		Json += FString::Printf(TEXT("    \"%s\""), *Variants[i]);
		if (i < Variants.Num() - 1)
		{
			Json += TEXT(",");
		}
		Json += TEXT("\n");
	}
	Json += TEXT("  ],\n");
	
	Json += FString::Printf(TEXT("  \"SelectedEnvironment\": \"%s\",\n"), *Environment);
	Json += FString::Printf(TEXT("  \"SelectedCamera\": \"%s\"\n"), *Camera);
	Json += TEXT("}");
	
	return Json;
}
