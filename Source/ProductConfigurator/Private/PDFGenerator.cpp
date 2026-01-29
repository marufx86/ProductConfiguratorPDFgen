// Copyright Epic Games, Inc. All Rights Reserved.

#include "PDFGenerator.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Misc/Paths.h"

FString FPDFGenerator::EscapePDFString(const FString& Input)
{
	// Escape special PDF characters: backslash, parentheses
	FString Result = Input;
	Result.ReplaceInline(TEXT("\\"), TEXT("\\\\"));
	Result.ReplaceInline(TEXT("("), TEXT("\\("));
	Result.ReplaceInline(TEXT(")"), TEXT("\\)"));
	return Result;
}

FString FPDFGenerator::BuildPDFContentStream(
	const FString& ConfigName,
	const FString& Timestamp,
	const TArray<FString>& Variants,
	const FString& Environment,
	const FString& Camera)
{
	TArray<FString> Lines;
	
	// Begin text block
	Lines.Add(TEXT("BT"));
	
	// Title: Product Configuration Summary (Bold, 16pt)
	Lines.Add(TEXT("/F2 16 Tf"));
	Lines.Add(TEXT("50 750 Td"));
	Lines.Add(FString::Printf(TEXT("(%s) Tj"), *EscapePDFString(TEXT("Product Configuration Summary"))));
	
	// Configuration name (Regular, 11pt)
	Lines.Add(TEXT("0 -25 Td /F1 11 Tf"));
	Lines.Add(FString::Printf(TEXT("(Configuration: %s) Tj"), *EscapePDFString(ConfigName)));
	
	// Timestamp
	Lines.Add(TEXT("0 -18 Td"));
	Lines.Add(FString::Printf(TEXT("(Timestamp: %s) Tj"), *EscapePDFString(Timestamp)));
	
	// Selected Variants header (Bold, 12pt)
	Lines.Add(TEXT("0 -30 Td /F2 12 Tf"));
	Lines.Add(TEXT("(Selected Variants:) Tj"));
	
	// Variant list (Regular, 10pt)
	Lines.Add(TEXT("0 -20 Td /F1 10 Tf"));
	
	// List variants (max 30)
	int32 MaxVariants = FMath::Min(Variants.Num(), 30);
	for (int32 i = 0; i < MaxVariants; ++i)
	{
		FString VariantLine = FString::Printf(TEXT("  %d. %s"), i + 1, *EscapePDFString(Variants[i]));
		Lines.Add(FString::Printf(TEXT("(%s) Tj 0 -14 Td"), *VariantLine));
	}
	
	// If more than 30 variants, show ellipsis
	if (Variants.Num() > 30)
	{
		FString MoreText = FString::Printf(TEXT("  ... and %d more"), Variants.Num() - 30);
		Lines.Add(FString::Printf(TEXT("(%s) Tj 0 -14 Td"), *MoreText));
	}
	
	// Environment (Bold, 11pt)
	Lines.Add(TEXT("0 -20 Td /F2 11 Tf"));
	Lines.Add(FString::Printf(TEXT("(Environment: %s) Tj"), *EscapePDFString(Environment)));
	
	// Camera
	Lines.Add(TEXT("0 -18 Td"));
	Lines.Add(FString::Printf(TEXT("(Camera: %s) Tj"), *EscapePDFString(Camera)));
	
	// End text block
	Lines.Add(TEXT("ET"));
	
	// Join with newlines
	return FString::Join(Lines, TEXT("\n"));
}

TArray<uint8> FPDFGenerator::BuildPDFDocument(const FString& ContentStream)
{
	// Convert content stream to Latin-1 (PDF standard encoding)
	FTCHARToUTF8 ContentUTF8(*ContentStream);
	int32 StreamLength = ContentUTF8.Length();
	
	TArray<FString> PDFLines;
	
	// PDF Header
	PDFLines.Add(TEXT("%PDF-1.4"));
	
	// Object 1: Catalog
	PDFLines.Add(TEXT("1 0 obj"));
	PDFLines.Add(TEXT("<< /Type /Catalog /Pages 2 0 R >>"));
	PDFLines.Add(TEXT("endobj"));
	
	// Object 2: Pages collection
	PDFLines.Add(TEXT("2 0 obj"));
	PDFLines.Add(TEXT("<< /Type /Pages /Kids [3 0 R] /Count 1 >>"));
	PDFLines.Add(TEXT("endobj"));
	
	// Object 3: Single page (8.5" x 11" = 612 x 792 points)
	PDFLines.Add(TEXT("3 0 obj"));
	PDFLines.Add(TEXT("<<"));
	PDFLines.Add(TEXT("/Type /Page"));
	PDFLines.Add(TEXT("/Parent 2 0 R"));
	PDFLines.Add(TEXT("/MediaBox [0 0 612 792]"));
	PDFLines.Add(TEXT("/Contents 4 0 R"));
	PDFLines.Add(TEXT("/Resources <<"));
	PDFLines.Add(TEXT("/Font <<"));
	PDFLines.Add(TEXT("/F1 << /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>"));
	PDFLines.Add(TEXT("/F2 << /Type /Font /Subtype /Type1 /BaseFont /Helvetica-Bold >>"));
	PDFLines.Add(TEXT(">>"));
	PDFLines.Add(TEXT(">>"));
	PDFLines.Add(TEXT(">>"));
	PDFLines.Add(TEXT("endobj"));
	
	// Object 4: Content stream
	PDFLines.Add(TEXT("4 0 obj"));
	PDFLines.Add(FString::Printf(TEXT("<< /Length %d >>"), StreamLength));
	PDFLines.Add(TEXT("stream"));
	PDFLines.Add(ContentStream);
	PDFLines.Add(TEXT("endstream"));
	PDFLines.Add(TEXT("endobj"));
	
	// Cross-reference table (simplified with fixed offsets)
	PDFLines.Add(TEXT("xref"));
	PDFLines.Add(TEXT("0 5"));
	PDFLines.Add(TEXT("0000000000 65535 f"));
	PDFLines.Add(TEXT("0000000009 00000 n"));
	PDFLines.Add(TEXT("0000000058 00000 n"));
	PDFLines.Add(TEXT("0000000115 00000 n"));
	PDFLines.Add(TEXT("0000000344 00000 n"));
	
	// Trailer
	PDFLines.Add(TEXT("trailer"));
	PDFLines.Add(TEXT("<< /Size 5 /Root 1 0 R >>"));
	PDFLines.Add(TEXT("startxref"));
	PDFLines.Add(FString::Printf(TEXT("%d"), 400 + StreamLength));
	PDFLines.Add(TEXT("%%EOF"));
	
	// Join all lines
	FString PDFContent = FString::Join(PDFLines, TEXT("\n"));
	
	// Convert to byte array (Latin-1 encoding)
	FTCHARToUTF8 ContentConverter(*PDFContent);
	TArray<uint8> PDFBytes;
	PDFBytes.Append((uint8*)ContentConverter.Get(), ContentConverter.Length());
	
	return PDFBytes;
}

bool FPDFGenerator::GeneratePDFFromJSON(const FString& JsonFilePath, const FString& PdfFilePath, FString& OutErrorMessage)
{
	OutErrorMessage.Empty();
	
	// Validate JSON file exists
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*JsonFilePath))
	{
		OutErrorMessage = FString::Printf(TEXT("JSON file not found: %s"), *JsonFilePath);
		return false;
	}
	
	// Load JSON file
	FString JsonString;
	if (!FFileHelper::LoadFileToString(JsonString, *JsonFilePath))
	{
		OutErrorMessage = TEXT("Failed to read JSON file");
		return false;
	}
	
	// Parse JSON
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	
	if (!FJsonSerializer::Deserialize(JsonReader, JsonObject) || !JsonObject.IsValid())
	{
		OutErrorMessage = TEXT("Failed to parse JSON file");
		return false;
	}
	
	// Extract data from JSON
	FString ConfigName = JsonObject->GetStringField(TEXT("ConfigurationName"));
	FString Timestamp = JsonObject->GetStringField(TEXT("Timestamp"));
	FString Environment = JsonObject->GetStringField(TEXT("SelectedEnvironment"));
	FString Camera = JsonObject->GetStringField(TEXT("SelectedCamera"));
	
	// Extract variants array
	TArray<FString> Variants;
	const TArray<TSharedPtr<FJsonValue>>* VariantsArray;
	if (JsonObject->TryGetArrayField(TEXT("SelectedVariants"), VariantsArray))
	{
		for (const TSharedPtr<FJsonValue>& VariantValue : *VariantsArray)
		{
			FString VariantString;
			if (VariantValue->TryGetString(VariantString))
			{
				Variants.Add(VariantString);
			}
		}
	}
	
	// Build PDF content stream
	FString ContentStream = BuildPDFContentStream(ConfigName, Timestamp, Variants, Environment, Camera);
	
	// Build complete PDF document
	TArray<uint8> PDFBytes = BuildPDFDocument(ContentStream);
	
	// Ensure output directory exists
	FString PDFDirectory = FPaths::GetPath(PdfFilePath);
	if (!PlatformFile.DirectoryExists(*PDFDirectory))
	{
		if (!PlatformFile.CreateDirectoryTree(*PDFDirectory))
		{
			OutErrorMessage = FString::Printf(TEXT("Failed to create directory: %s"), *PDFDirectory);
			return false;
		}
	}
	
	// Write PDF to file
	if (!FFileHelper::SaveArrayToFile(PDFBytes, *PdfFilePath))
	{
		OutErrorMessage = FString::Printf(TEXT("Failed to write PDF file: %s"), *PdfFilePath);
		return false;
	}
	
	UE_LOG(LogTemp, Log, TEXT("PDF generated successfully: %s"), *PdfFilePath);
	return true;
}
