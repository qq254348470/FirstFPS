// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FirstFPS : ModuleRules
{
	public FirstFPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","AIModule" });
	}
}
