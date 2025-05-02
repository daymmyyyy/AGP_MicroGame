using UnrealBuildTool;

public class A2_AGPClientTarget : TargetRules
{
	public A2_AGPClientTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		Type = TargetType.Client;
		ExtraModuleNames.Add("A2_AGP");
	}
}
