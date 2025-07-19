using UnrealBuildTool;

public class FBIKGraphNodes : ModuleRules
{
    public FBIKGraphNodes(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "FBIK",
                "AnimGraph",
                "AnimGraphRuntime",
                "BlueprintGraph",
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