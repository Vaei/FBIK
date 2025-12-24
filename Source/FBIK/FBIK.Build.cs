// Copyright (c) Jared Taylor

using UnrealBuildTool;

public class FBIK : ModuleRules
{
	public FBIK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"AnimGraphRuntime",
				"LocoPBIK",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
			}
			);
	}
}
