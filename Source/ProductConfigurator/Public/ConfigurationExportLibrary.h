// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConfigurationExportLibrary.generated.h"

/**
 * Configuration data structure matching STRUCT_ConfigurationData
 */
USTRUCT(BlueprintType)
struct FConfigurationData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Configuration")
	FString ConfigurationName;

	UPROPERTY(BlueprintReadWrite, Category = "Configuration")
	FString Timestamp;

	UPROPERTY(BlueprintReadWrite, Category = "Configuration")
	TArray<FString> SelectedVariants;

	UPROPERTY(BlueprintReadWrite, Category = "Configuration")
	FString SelectedEnvironment;

	UPROPERTY(BlueprintReadWrite, Category = "Configuration")
	FString SelectedCamera;
};

/**
 * Blueprint Function Library for configuration export and PDF generation
 */
UCLASS()
class PRODUCTCONFIGURATOR_API UConfigurationExportLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Export configuration data to JSON file in project Saved directory
	 * @param ConfigData Configuration data struct to export
	 * @param ConfigurationName Custom name for the configuration (optional)
	 * @param Success Whether export succeeded
	 * @param FilePath Path to the exported JSON file
	 */
	UFUNCTION(BlueprintCallable, Category = "Configuration|Export")
	static void ExportConfigurationToJSON(
		const FConfigurationData& ConfigData,
		const FString& ConfigurationName,
		bool& Success,
		FString& FilePath
	);

	/**
	 * Generate PDF summary from JSON configuration file
	 * @param JsonFilePath Path to JSON file to convert
	 * @param Success Whether PDF generation launched successfully
	 * @param PDFOutputPath Path where PDF will be generated
	 * @param ErrorMessage Error message if generation failed
	 */
	UFUNCTION(BlueprintCallable, Category = "Configuration|Export")
	static void GeneratePDFFromJSON(
		const FString& JsonFilePath,
		bool& Success,
		FString& PDFOutputPath,
		FString& ErrorMessage
	);

	/**
	 * Collect VariantSet data from LevelVariantSetsActor and export to PDF
	 * This is a convenience function that handles the entire export workflow
	 * @param LevelVariantSetsActor The actor containing the VariantSet data
	 * @param ConfigurationName Custom name for the configuration (optional)
	 * @param Success Whether the export succeeded
	 * @param PDFOutputPath Path to the generated PDF file
	 * @param ErrorMessage Error message if export failed
	 */
	UFUNCTION(BlueprintCallable, Category = "Configuration|Export")
	static void ExportVariantSetsToPDF(
		class ALevelVariantSetsActor* LevelVariantSetsActor,
		const FString& ConfigurationName,
		bool& Success,
		FString& PDFOutputPath,
		FString& ErrorMessage
	);

	/**
	 * Get current timestamp as formatted string
	 * @return Timestamp string in YYYY-MM-DD_HH-MM-SS format
	 */
	UFUNCTION(BlueprintPure, Category = "Configuration|Utility")
	static FString GetFormattedTimestamp();

	/**
	 * Get project Saved directory path
	 * @return Full path to project Saved directory
	 */
	UFUNCTION(BlueprintPure, Category = "Configuration|Utility")
	static FString GetProjectSavedDirectory();

	/**
	 * Convert struct to JSON string (generic version)
	 * @param StructDefinition The UStruct definition
	 * @param StructPtr Pointer to struct data
	 * @param OutJsonString Output JSON string
	 * @return Whether conversion succeeded
	 */
	static bool StructToJsonString(
		const UScriptStruct* StructDefinition,
		const void* StructPtr,
		FString& OutJsonString
	);
};
