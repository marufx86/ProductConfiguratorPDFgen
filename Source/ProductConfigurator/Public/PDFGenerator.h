// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/UnrealString.h"

/**
 * Pure C++ PDF generator using PDF 1.4 specification.
 * No external dependencies - works in packaged builds.
 */
class PRODUCTCONFIGURATOR_API FPDFGenerator
{
public:
	/**
	 * Generate a PDF file from JSON configuration data.
	 * 
	 * @param JsonFilePath - Full path to the JSON configuration file
	 * @param PdfFilePath - Full path where the PDF should be saved
	 * @param OutErrorMessage - Error message if generation fails
	 * @return true if PDF was successfully generated
	 */
	static bool GeneratePDFFromJSON(const FString& JsonFilePath, const FString& PdfFilePath, FString& OutErrorMessage);

private:
	/**
	 * Escape special characters for PDF text content.
	 * Handles backslashes, parentheses which have special meaning in PDF.
	 */
	static FString EscapePDFString(const FString& Input);

	/**
	 * Build the PDF content stream (text and positioning commands).
	 */
	static FString BuildPDFContentStream(
		const FString& ConfigName,
		const FString& Timestamp,
		const TArray<FString>& Variants,
		const FString& Environment,
		const FString& Camera);

	/**
	 * Build the complete PDF structure (objects, xref table, trailer).
	 */
	static TArray<uint8> BuildPDFDocument(const FString& ContentStream);
};
