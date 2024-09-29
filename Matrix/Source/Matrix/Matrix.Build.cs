// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Matrix : ModuleRules
{
	public Matrix(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { "Matrix" });

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayAbilities",
			"UMG", 
			"GameplayTags", 
			"GameplayTasks",
            "AnimGraphRuntime",
            "MotionWarping",
        });
	}
}
