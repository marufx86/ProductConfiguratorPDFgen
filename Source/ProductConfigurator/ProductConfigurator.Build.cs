// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProductConfigurator : ModuleRules
{
	public ProductConfigurator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine",
			"Json",
			"JsonUtilities",
			"VariantManagerContent"
		});

		PrivateDependencyModuleNames.AddRange(new string[] 
		{
			"Slate",
			"SlateCore"
		});
	}
}
