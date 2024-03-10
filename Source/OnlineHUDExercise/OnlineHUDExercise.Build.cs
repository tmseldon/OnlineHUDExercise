// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OnlineHUDExercise : ModuleRules
{
	public OnlineHUDExercise(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"UMG", 
			"Json", 
			"JsonUtilities", 
			"StructUtils", 
		});
    }
}
