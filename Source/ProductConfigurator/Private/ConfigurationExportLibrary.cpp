// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConfigurationExportLibrary.h" // Keep this as the first include

// --- ADD THESE LINES ---
#include "VariantManagerContent/Public/VariantSet.h"
#include "VariantManagerContent/Public/Variant.h"
#include "VariantManagerContent/Public/LevelVariantSets.h"
// -----------------------
#include "ConfigurationExportLibrary.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/DateTime.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/PlatformProcess.h"
#include "JsonObjectConverter.h"
#include "LevelVariantSets.h"
#include "LevelVariantSetsActor.h"

void UConfigurationExportLibrary::ExportConfigurationToJSON(
	const FConfigurationData& ConfigData,
	const FString& ConfigurationName,
	bool& Success,
	FString& FilePath)
{
	Success = false;

	// Build file path
	FString SaveDir = FPaths::ProjectSavedDir() / TEXT("Configurations");
	FString FileName = ConfigurationName.IsEmpty() 
		? FString::Printf(TEXT("Config_%s.json"), *GetFormattedTimestamp())
		: FString::Printf(TEXT("%s_%s.json"), *ConfigurationName, *GetFormattedTimestamp());
	
	FilePath = SaveDir / FileName;

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

	// Convert struct to JSON
	FString JsonString;
	if (!FJsonObjectConverter::UStructToJsonObjectString(ConfigData, JsonString))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to convert configuration to JSON"));
		return;
	}

	// Save to file
	if (FFileHelper::SaveStringToFile(JsonString, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		Success = true;
		UE_LOG(LogTemp, Log, TEXT("Configuration exported to: %s"), *FilePath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save JSON file: %s"), *FilePath);
	}
}

void UConfigurationExportLibrary::GeneratePDFFromJSON(
	const FString& JsonFilePath,
	bool& Success,
	FString& PDFOutputPath,
	FString& ErrorMessage)
{
	Success = false;
	ErrorMessage = TEXT("");

	// Validate input
	if (JsonFilePath.IsEmpty())
	{
		ErrorMessage = TEXT("JSON file path is empty");
		return;
	}

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*JsonFilePath))
	{
		ErrorMessage = FString::Printf(TEXT("JSON file not found: %s"), *JsonFilePath);
		return;
	}

	// Build PDF output path
	FString PDFDir = FPaths::ProjectSavedDir() / TEXT("PDFs");
	FString BaseFileName = FPaths::GetBaseFilename(JsonFilePath);
	PDFOutputPath = PDFDir / (BaseFileName + TEXT(".pdf"));

	// Ensure PDF directory exists
	if (!PlatformFile.DirectoryExists(*PDFDir))
	{
		if (!PlatformFile.CreateDirectoryTree(*PDFDir))
		{
			ErrorMessage = FString::Printf(TEXT("Failed to create PDF directory: %s"), *PDFDir);
			return;
		}
	}

	// Build command for PDF generator
	// Adjust this path based on your PDF generator location
	FString ScriptPath = FPaths::ProjectDir() / TEXT("Scripts/generate_pdf.py");
	
	if (!PlatformFile.FileExists(*ScriptPath))
	{
		ErrorMessage = FString::Printf(TEXT("PDF generator script not found: %s"), *ScriptPath);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ErrorMessage);
		UE_LOG(LogTemp, Warning, TEXT("Create Scripts/generate_pdf.py or configure your PDF generator path"));
		return;
	}

	// Launch Python script to generate PDF
	// Command: python Scripts/generate_pdf.py "<json_path>" "<pdf_path>"
	// Try 'py' launcher first (Windows Python launcher), then 'python'
	FString PythonExecutable = TEXT("py");
	FString Arguments = FString::Printf(TEXT("-3 \"%s\" \"%s\" \"%s\""), *ScriptPath, *JsonFilePath, *PDFOutputPath);

	UE_LOG(LogTemp, Log, TEXT("Launching PDF generator: %s %s"), *PythonExecutable, *Arguments);

	// Try 'py' launcher first
	FProcHandle ProcessHandle = FPlatformProcess::CreateProc(
		*PythonExecutable,
		*Arguments,
		true,
		false,
		false,
		nullptr,
		0,
		nullptr,
		nullptr);
	
	// If 'py' failed, try 'python' directly
	if (!ProcessHandle.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("'py' launcher failed, trying 'python' directly"));
		PythonExecutable = TEXT("python");
		Arguments = FString::Printf(TEXT("\"%s\" \"%s\" \"%s\""), *ScriptPath, *JsonFilePath, *PDFOutputPath);
		
		ProcessHandle = FPlatformProcess::CreateProc(
			*PythonExecutable,
			*Arguments,
			true,
			false,
			false,
			nullptr,
			0,
			nullptr,
			nullptr);
	}

	if (ProcessHandle.IsValid())
	{
		Success = true;
		UE_LOG(LogTemp, Log, TEXT("PDF generation process launched. Output: %s"), *PDFOutputPath);
		FPlatformProcess::CloseProc(ProcessHandle);
	}
	else
	{
		ErrorMessage = TEXT("Failed to launch PDF generation process. Ensure Python is installed and in PATH.");
		UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
	}
}

void UConfigurationExportLibrary::ExportVariantSetsToPDF(
	ALevelVariantSetsActor* LevelVariantSetsActor,
	const FString& ConfigurationName,
	bool& Success,
	FString& PDFOutputPath,
	FString& ErrorMessage)
{
	Success = false;
	PDFOutputPath = TEXT("");
	ErrorMessage = TEXT("");

	// Validate input
	if (!LevelVariantSetsActor)
	{
		ErrorMessage = TEXT("LevelVariantSetsActor is null. Please ensure a LevelVariantSetsActor exists in the level.");
		UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
		return;
	}

	// Get the LevelVariantSets asset
	ULevelVariantSets* VariantSets = LevelVariantSetsActor->GetLevelVariantSets();
	if (!VariantSets)
	{
		ErrorMessage = TEXT("No LevelVariantSets asset found in the actor.");
		UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
		return;
	}

	// Collect all variant data
	FConfigurationData ConfigData;
	ConfigData.ConfigurationName = ConfigurationName.IsEmpty() ? TEXT("ProductConfiguration") : ConfigurationName;
	ConfigData.Timestamp = GetFormattedTimestamp();
	ConfigData.SelectedEnvironment = TEXT("Default");
	ConfigData.SelectedCamera = TEXT("Default");

	// Iterate through all VariantSets and their Variants
	int32 NumVariantSets = VariantSets->GetNumVariantSets();
	UE_LOG(LogTemp, Log, TEXT("Found %d variant sets"), NumVariantSets);

	for (int32 i = 0; i < NumVariantSets; ++i)
	{
		UVariantSet* VariantSet = VariantSets->GetVariantSet(i);
		if (VariantSet)
		{
			FString VariantSetName = VariantSet->GetDisplayText().ToString();
			int32 NumVariants = VariantSet->GetNumVariants();
			
			for (int32 j = 0; j < NumVariants; ++j)
			{
				UVariant* Variant = VariantSet->GetVariant(j);
				if (Variant)
				{
					FString VariantName = Variant->GetDisplayText().ToString();
					FString FullVariantPath = VariantSetName + TEXT(" > ") + VariantName;
					ConfigData.SelectedVariants.Add(FullVariantPath);
				}
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Collected %d variants"), ConfigData.SelectedVariants.Num());

	// Export to JSON
	FString JsonFilePath;
	bool JsonSuccess = false;
	ExportConfigurationToJSON(ConfigData, ConfigData.ConfigurationName, JsonSuccess, JsonFilePath);

	if (!JsonSuccess)
	{
		ErrorMessage = TEXT("Failed to export configuration to JSON");
		return;
	}

	// Generate PDF from JSON
	GeneratePDFFromJSON(JsonFilePath, Success, PDFOutputPath, ErrorMessage);
}

FString UConfigurationExportLibrary::GetFormattedTimestamp()
{
	FDateTime Now = FDateTime::Now();
	return Now.ToString(TEXT("%Y-%m-%d_%H-%M-%S"));
}

FString UConfigurationExportLibrary::GetProjectSavedDirectory()
{
	return FPaths::ProjectSavedDir();
}

bool UConfigurationExportLibrary::StructToJsonString(
	const UScriptStruct* StructDefinition,
	const void* StructPtr,
	FString& OutJsonString)
{
	if (!StructDefinition || !StructPtr)
	{
		return false;
	}

	return FJsonObjectConverter::UStructToJsonObjectString(StructDefinition, StructPtr, OutJsonString);
}
