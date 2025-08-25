// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Arkanoid : ModuleRules
{
	public Arkanoid(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[]
		{
			"Arkanoid",
			"Arkanoid/Public/Bonuses",
			"Arkanoid/Public/Components",
			"Arkanoid/Public/Framework",
			"Arkanoid/Public/World"
		});
	}
}