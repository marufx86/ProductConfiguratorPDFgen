// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConfigurationExportLibrary.h" // Keep this as the first include

// --- ADD THESE LINES ---
#include "VariantManagerContent/Public/VariantSet.h"
#include "VariantManagerContent/Public/Variant.h"
#include "VariantManagerContent/Public/LevelVariantSets.h"
// -----------------------
#include "PDFGenerator.h"
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
	// Use ProjectSavedDir for packaged builds, falls back to ProjectDir/Saved in editor
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
	// Use ProjectSavedDir for packaged builds compatibility
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

	// Use C++ PDF generator (works in packaged builds)
	if (FPDFGenerator::GeneratePDFFromJSON(JsonFilePath, PDFOutputPath, ErrorMessage))
	{
		Success = true;
		UE_LOG(LogTemp, Log, TEXT("PDF generated successfully: %s"), *PDFOutputPath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PDF generation failed: %s"), *ErrorMessage);
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
	// Pass true to load the asset if it's not already loaded
	ULevelVariantSets* VariantSets = LevelVariantSetsActor->GetLevelVariantSets(true);
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
			
			// Find the active variant in this set
			FString ActiveVariantName = TEXT("None");
			for (int32 j = 0; j < NumVariants; ++j)
			{
				UVariant* Variant = VariantSet->GetVariant(j);
				// Only collect if this variant is active
				if (Variant && Variant->IsActive())
				{
					ActiveVariantName = Variant->GetDisplayText().ToString();
					break; // Found the active one, stop
				}
			}
			// Add variant set with its active variant
			FString FullVariantPath = VariantSetName + TEXT(": ") + ActiveVariantName;
			ConfigData.SelectedVariants.Add(FullVariantPath);
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

void UConfigurationExportLibrary::ExportSelectedVariantsToPDF(
	AActor* ConfiguratorActor,
	const FString& ConfigurationName,
	bool& Success,
	FString& PDFOutputPath,
	FString& ErrorMessage)
{
	Success = false;
	PDFOutputPath = TEXT("");
	ErrorMessage = TEXT("");

	// Validate input
	if (!ConfiguratorActor)
	{
		ErrorMessage = TEXT("ConfiguratorActor is null.");
		UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
		return;
	}

	// Get ObjectVariantSets array property using reflection
	FProperty* VariantsProp = ConfiguratorActor->GetClass()->FindPropertyByName(TEXT("ObjectVariantSets"));
	if (!VariantsProp)
	{
		ErrorMessage = TEXT("ObjectVariantSets property not found on ConfiguratorActor.");
		UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
		return;
	}

	// Build configuration data from selected variants
	FConfigurationData ConfigData;
	ConfigData.ConfigurationName = ConfigurationName.IsEmpty() ? TEXT("ProductConfiguration") : ConfigurationName;
	ConfigData.Timestamp = GetFormattedTimestamp();
	ConfigData.SelectedEnvironment = TEXT("Default");
	ConfigData.SelectedCamera = TEXT("Default");

	// Note: This is a simplified implementation that exports all variants
	// For full implementation, you would need to parse the ObjectVariantSets struct array
	// and read the currentIndex from each STRUCT_VarSet to determine selected variants
	
	UE_LOG(LogTemp, Warning, TEXT("ExportSelectedVariantsToPDF: Using fallback implementation. "));
	UE_LOG(LogTemp, Warning, TEXT("Consider using ExportVariantSetsToPDF with LevelVariantSetsActor for full functionality."));

	// For now, add a placeholder
	ConfigData.SelectedVariants.Add(TEXT("Export from BP_Configurator - Implementation needed"));

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

	if (Success)
	{
		UE_LOG(LogTemp, Log, TEXT("PDF exported successfully from BP_Configurator: %s"), *PDFOutputPath);
	}
}
