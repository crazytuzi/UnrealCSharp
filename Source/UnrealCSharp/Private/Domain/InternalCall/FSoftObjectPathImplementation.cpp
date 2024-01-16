#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterSoftObjectPath
{
	FRegisterSoftObjectPath()
	{
		TReflectionClassBuilder<FSoftObjectPath>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, const FSoftObjectPath&),
			             {"Other"})
			.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, const FString&),
			             {"Path"})
			.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, FName),
			             {"Path"})
			.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, FName, FString),
			             {"InAssetPathName", "InSubPathString"})
			.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, const UObject*),
			             {"InObject"})
			.Function("ToString", BINDING_OVERLOAD(FString(FSoftObjectPath::*)()const, &FSoftObjectPath::ToString))
			.Function("GetAssetPathName", BINDING_FUNCTION(&FSoftObjectPath::GetAssetName))
			.Function("SetAssetPathName", BINDING_FUNCTION(&FSoftObjectPath::SetAssetPathName),
			          {"InAssetPathName"})
			.Function("GetAssetPathString", BINDING_FUNCTION(&FSoftObjectPath::GetAssetPathString))
			.Function("GetSubPathString", BINDING_FUNCTION(&FSoftObjectPath::GetSubPathString))
			.Function("SetSubPathString", BINDING_FUNCTION(&FSoftObjectPath::SetSubPathString),
			          {"InSubPathString"})
			.Function("GetLongPackageName", BINDING_FUNCTION(&FSoftObjectPath::GetLongPackageName))
			.Function("GetLongPackageFName", BINDING_FUNCTION(&FSoftObjectPath::GetLongPackageFName))
			.Function("GetAssetName", BINDING_FUNCTION(&FSoftObjectPath::GetAssetName))
			.Function("SetPath", BINDING_OVERLOAD(void(FSoftObjectPath::*)(FName), &FSoftObjectPath::SetPath),
			          {"Path"})
			.Function("SetPath", BINDING_OVERLOAD(void(FSoftObjectPath::*)(const FString&), &FSoftObjectPath::SetPath),
			          {"Path"})
			.Function("ResolveObject", BINDING_FUNCTION(&FSoftObjectPath::ResolveObject))
			.Function("Reset", BINDING_FUNCTION(&FSoftObjectPath::Reset))
			.Function("IsValid", BINDING_FUNCTION(&FSoftObjectPath::IsValid))
			.Function("IsNull", BINDING_FUNCTION(&FSoftObjectPath::IsNull))
			.Function("IsAsset", BINDING_FUNCTION(&FSoftObjectPath::IsAsset))
			.Function("IsSubobject", BINDING_FUNCTION(&FSoftObjectPath::IsSubobject))
			.Function("FixupCoreRedirects", BINDING_FUNCTION(&FSoftObjectPath::FixupCoreRedirects))
			.Function("GetCurrentTag", BINDING_FUNCTION(&FSoftObjectPath::GetCurrentTag))
			.Function("InvalidateTag", BINDING_FUNCTION(&FSoftObjectPath::InvalidateTag))
			.Function("GetOrCreateIDForObject", BINDING_FUNCTION(&FSoftObjectPath::GetOrCreateIDForObject),
			          {"Object"})
			.Function("AddPIEPackageName", BINDING_FUNCTION(&FSoftObjectPath::AddPIEPackageName),
			          {"NewPIEPackageName"})
			.Function("ClearPIEPackageNames", BINDING_FUNCTION(&FSoftObjectPath::ClearPIEPackageNames))
			.Register();
	}
};

static FRegisterSoftObjectPath RegisterSoftObjectPath;
