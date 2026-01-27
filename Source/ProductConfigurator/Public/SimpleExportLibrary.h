// Simple Export Library for Product Configurator

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimpleExportLibrary.generated.h"

/**
 * Simple Blueprint Function Library for exporting configuration data
 * Works in packaged games
 */
UCLASS()
class PRODUCTCONFIGURATOR_API USimpleExportLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Export a string to a JSON file in the Saved/Configurations directory
	 * @param JsonContent The JSON string to save
	 * @param FileName Custom filename (without .json extension)
	 * @param Success Whether the export succeeded
	 * @param FilePath Full path to the saved file
	 */
	UFUNCTION(BlueprintCallable, Category = "Configuration|Export")
	static void ExportStringToJSON(
		const FString& JsonContent,
		const FString& FileName,
		bool& Success,
		FString& FilePath
	);

	/**
	 * Get current timestamp as formatted string
	 * @return Timestamp string in YYYY-MM-DD_HH-MM-SS format
	 */
	UFUNCTION(BlueprintPure, Category = "Configuration|Utility")
	static FString GetTimestamp();

	/**
	 * Build a JSON string from configuration data
	 * @param ConfigName Configuration name
	 * @param Timestamp Timestamp string
	 * @param Variants Array of selected variant names
	 * @param Environment Selected environment name
	 * @param Camera Selected camera name
	 * @return JSON string
	 */
	UFUNCTION(BlueprintPure, Category = "Configuration|Utility")
	static FString BuildConfigJSON(
		const FString& ConfigName,
		const FString& Timestamp,
		const TArray<FString>& Variants,
		const FString& Environment,
		const FString& Camera
	);
};
