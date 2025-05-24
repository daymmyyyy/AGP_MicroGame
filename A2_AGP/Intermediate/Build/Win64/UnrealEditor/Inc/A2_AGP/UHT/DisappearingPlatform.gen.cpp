// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "A2_AGP/DisappearingPlatform.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDisappearingPlatform() {}

// Begin Cross Module References
A2_AGP_API UClass* Z_Construct_UClass_ADisappearingPlatform();
A2_AGP_API UClass* Z_Construct_UClass_ADisappearingPlatform_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AActor();
UPackage* Z_Construct_UPackage__Script_A2_AGP();
// End Cross Module References

// Begin Class ADisappearingPlatform
void ADisappearingPlatform::StaticRegisterNativesADisappearingPlatform()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ADisappearingPlatform);
UClass* Z_Construct_UClass_ADisappearingPlatform_NoRegister()
{
	return ADisappearingPlatform::StaticClass();
}
struct Z_Construct_UClass_ADisappearingPlatform_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "DisappearingPlatform.h" },
		{ "ModuleRelativePath", "DisappearingPlatform.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADisappearingPlatform>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ADisappearingPlatform_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_A2_AGP,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADisappearingPlatform_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ADisappearingPlatform_Statics::ClassParams = {
	&ADisappearingPlatform::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADisappearingPlatform_Statics::Class_MetaDataParams), Z_Construct_UClass_ADisappearingPlatform_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ADisappearingPlatform()
{
	if (!Z_Registration_Info_UClass_ADisappearingPlatform.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADisappearingPlatform.OuterSingleton, Z_Construct_UClass_ADisappearingPlatform_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ADisappearingPlatform.OuterSingleton;
}
template<> A2_AGP_API UClass* StaticClass<ADisappearingPlatform>()
{
	return ADisappearingPlatform::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ADisappearingPlatform);
ADisappearingPlatform::~ADisappearingPlatform() {}
// End Class ADisappearingPlatform

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_dayan_OneDrive_Documents_GitHub_AGP_MicroGame_A2_AGP_Source_A2_AGP_DisappearingPlatform_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADisappearingPlatform, ADisappearingPlatform::StaticClass, TEXT("ADisappearingPlatform"), &Z_Registration_Info_UClass_ADisappearingPlatform, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADisappearingPlatform), 1552387679U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_dayan_OneDrive_Documents_GitHub_AGP_MicroGame_A2_AGP_Source_A2_AGP_DisappearingPlatform_h_4020094388(TEXT("/Script/A2_AGP"),
	Z_CompiledInDeferFile_FID_Users_dayan_OneDrive_Documents_GitHub_AGP_MicroGame_A2_AGP_Source_A2_AGP_DisappearingPlatform_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_dayan_OneDrive_Documents_GitHub_AGP_MicroGame_A2_AGP_Source_A2_AGP_DisappearingPlatform_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
