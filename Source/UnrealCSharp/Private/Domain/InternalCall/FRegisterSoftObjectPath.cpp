#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterSoftObjectPath
{
	FRegisterSoftObjectPath()
	{
		TBindingClassBuilder<FSoftObjectPath>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, const FSoftObjectPath&),
			             TArray<FString>{"Other"})
			.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, const FString&),
			             TArray<FString>{"Path"})
			.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, FName),
			             TArray<FString>{"Path"})
			.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, FName, FString),
			             TArray<FString>{"InAssetPathName", "InSubPathString"})
			.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, const UObject*),
			             TArray<FString>{"InObject"})
			.Function("ToString", BINDING_OVERLOAD(FString(FSoftObjectPath::*)()const, &FSoftObjectPath::ToString,
			                                       EFunctionInteract::New))
			.Function("GetAssetPathName", BINDING_FUNCTION(&FSoftObjectPath::GetAssetName))
			.Function("SetAssetPathName", BINDING_FUNCTION(&FSoftObjectPath::SetAssetPathName,
			                                               TArray<FString>{"InAssetPathName"}))
			.Function("GetAssetPathString", BINDING_FUNCTION(&FSoftObjectPath::GetAssetPathString))
			.Function("GetSubPathString", BINDING_FUNCTION(&FSoftObjectPath::GetSubPathString))
			.Function("SetSubPathString", BINDING_FUNCTION(&FSoftObjectPath::SetSubPathString,
			                                               TArray<FString>{"InSubPathString"}))
			.Function("GetLongPackageName", BINDING_FUNCTION(&FSoftObjectPath::GetLongPackageName))
			.Function("GetLongPackageFName", BINDING_FUNCTION(&FSoftObjectPath::GetLongPackageFName))
			.Function("GetAssetName", BINDING_FUNCTION(&FSoftObjectPath::GetAssetName))
			.Function("SetPath", BINDING_OVERLOAD(void(FSoftObjectPath::*)(FName), &FSoftObjectPath::SetPath,
			                                      TArray<FString>{"Path"}))
			.Function("SetPath", BINDING_OVERLOAD(void(FSoftObjectPath::*)(const FString&), &FSoftObjectPath::SetPath,
			                                      TArray<FString>{"Path"}))
			.Function("ResolveObject", BINDING_FUNCTION(&FSoftObjectPath::ResolveObject))
			.Function("Reset", BINDING_FUNCTION(&FSoftObjectPath::Reset))
			.Function("IsValid", BINDING_FUNCTION(&FSoftObjectPath::IsValid))
			.Function("IsNull", BINDING_FUNCTION(&FSoftObjectPath::IsNull))
			.Function("IsAsset", BINDING_FUNCTION(&FSoftObjectPath::IsAsset))
			.Function("IsSubobject", BINDING_FUNCTION(&FSoftObjectPath::IsSubobject))
			.Function("FixupCoreRedirects", BINDING_FUNCTION(&FSoftObjectPath::FixupCoreRedirects))
			.Function("GetCurrentTag", BINDING_FUNCTION(&FSoftObjectPath::GetCurrentTag))
			.Function("InvalidateTag", BINDING_FUNCTION(&FSoftObjectPath::InvalidateTag))
			.Function("GetOrCreateIDForObject", BINDING_FUNCTION(&FSoftObjectPath::GetOrCreateIDForObject,
			                                                     TArray<FString>{"Object"}))
			.Function("AddPIEPackageName", BINDING_FUNCTION(&FSoftObjectPath::AddPIEPackageName,
			                                                TArray<FString>{"NewPIEPackageName"}))
			.Function("ClearPIEPackageNames", BINDING_FUNCTION(&FSoftObjectPath::ClearPIEPackageNames))
			.Register();
	}
};

static FRegisterSoftObjectPath RegisterSoftObjectPath;
