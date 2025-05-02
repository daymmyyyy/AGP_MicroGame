using UnrealBuildTool;

public class A2_AGPTarget : TargetRules
{
	public A2_AGPTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		Type = TargetType.Game;
		ExtraModuleNames.Add("A2_AGP");
	}
}
