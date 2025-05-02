using UnrealBuildTool;

public class A2_AGPEditorTarget : TargetRules
{
	public A2_AGPEditorTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		Type = TargetType.Editor;
		ExtraModuleNames.Add("A2_AGP");
	}
}
