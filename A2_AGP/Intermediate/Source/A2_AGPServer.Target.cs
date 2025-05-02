using UnrealBuildTool;

public class A2_AGPServerTarget : TargetRules
{
	public A2_AGPServerTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		Type = TargetType.Server;
		ExtraModuleNames.Add("A2_AGP");
	}
}
