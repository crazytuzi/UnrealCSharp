#include "Binding/Class/TBindingClassBuilder.inl"
#include "Macro/NamespaceMacro.h"
#if !UE_U_STRUCT_F_SOFT_OBJECT_PATH
#include "Binding/ScriptStruct/TScriptStruct.inl"
#endif

#if UE_U_STRUCT_F_SOFT_OBJECT_PATH
BINDING_STRUCT(FSoftObjectPath)
#endif

namespace
{
	struct FRegisterSoftObjectPath
	{
		FRegisterSoftObjectPath()
		{
			TBindingClassBuilder<FSoftObjectPath>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, const FSoftObjectPath&),
				             TArray<FString>{"Other"})
				.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, const FString&),
				             TArray<FString>{"Path"})
#if UE_F_SOFT_OBJECT_PATH_CONSTRUCTOR_F_NAME
				.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, FName),
				             TArray<FString>{"Path"})
#endif
#if UE_F_SOFT_OBJECT_PATH_CONSTRUCTOR_F_NAME_F_STRING
				.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, FName, FString),
				             TArray<FString>{"InAssetPathName", "InSubPathString"})
#endif
				.Constructor(BINDING_CONSTRUCTOR(FSoftObjectPath, const UObject*),
				             TArray<FString>{"InObject"})
				.Function("ToString", BINDING_OVERLOAD(FString(FSoftObjectPath::*)()const, &FSoftObjectPath::ToString,
				                                       EFunctionInteract::New))
				.Function("GetAssetPathName", BINDING_FUNCTION(&FSoftObjectPath::GetAssetName))
#if UE_F_SOFT_OBJECT_PATH_SET_ASSET_PATH_NAME
				.Function("SetAssetPathName", BINDING_FUNCTION(&FSoftObjectPath::SetAssetPathName,
				                                               TArray<FString>{"InAssetPathName"}))
#endif
				.Function("GetAssetPathString", BINDING_FUNCTION(&FSoftObjectPath::GetAssetPathString))
				.Function("GetSubPathString", BINDING_FUNCTION(&FSoftObjectPath::GetSubPathString))
#if UE_F_SOFT_OBJECT_PATH_SET_SUB_PATH_STRING
				.Function("SetSubPathString", BINDING_FUNCTION(&FSoftObjectPath::SetSubPathString,
				                                               TArray<FString>{"InSubPathString"}))
#endif
				.Function("GetLongPackageName", BINDING_FUNCTION(&FSoftObjectPath::GetLongPackageName))
				.Function("GetLongPackageFName", BINDING_FUNCTION(&FSoftObjectPath::GetLongPackageFName))
				.Function("GetAssetName", BINDING_FUNCTION(&FSoftObjectPath::GetAssetName))
#if UE_F_SOFT_OBJECT_PATH_SET_PATH_F_NAME
				.Function("SetPath", BINDING_OVERLOAD(void(FSoftObjectPath::*)(FName), &FSoftObjectPath::SetPath,
				                                      TArray<FString>{"Path"}))
#endif
				.Function("SetPath", BINDING_OVERLOAD(void(FSoftObjectPath::*)(const FString&),
				                                      &FSoftObjectPath::SetPath,
				                                      TArray<FString>{"Path"}))
				.Function("ResolveObject", BINDING_FUNCTION(&FSoftObjectPath::ResolveObject))
				.Function("Reset", BINDING_FUNCTION(&FSoftObjectPath::Reset))
				.Function("IsValid", BINDING_FUNCTION(&FSoftObjectPath::IsValid))
				.Function("IsNull", BINDING_FUNCTION(&FSoftObjectPath::IsNull))
				.Function("IsAsset", BINDING_FUNCTION(&FSoftObjectPath::IsAsset))
				.Function("IsSubobject", BINDING_FUNCTION(&FSoftObjectPath::IsSubobject))
				.Function("FixupCoreRedirects", BINDING_FUNCTION(&FSoftObjectPath::FixupCoreRedirects))
#if UE_F_SOFT_OBJECT_PATH_GET_CURRENT_TAG
				.Function("GetCurrentTag", BINDING_FUNCTION(&FSoftObjectPath::GetCurrentTag))
#endif
#if UE_F_SOFT_OBJECT_PATH_INVALIDATE_TAG
				.Function("InvalidateTag", BINDING_FUNCTION(&FSoftObjectPath::InvalidateTag))
#endif
#if UE_F_SOFT_OBJECT_PATH_GET_OR_CREATE_ID_FOR_OBJECT_U_OBJECT
				.Function("GetOrCreateIDForObject", BINDING_OVERLOAD(FSoftObjectPath(*)(const UObject*),
				                                                     &FSoftObjectPath::GetOrCreateIDForObject,
				                                                     TArray<FString>{"Object"}))
#else
				.Function("GetOrCreateIDForObject", BINDING_FUNCTION(&FSoftObjectPath::GetOrCreateIDForObject,
				                                                     TArray<FString>{"Object"}))
#endif
				.Function("AddPIEPackageName", BINDING_FUNCTION(&FSoftObjectPath::AddPIEPackageName,
				                                                TArray<FString>{"NewPIEPackageName"}))
				.Function("ClearPIEPackageNames", BINDING_FUNCTION(&FSoftObjectPath::ClearPIEPackageNames));
		}
	};

	[[maybe_unused]] FRegisterSoftObjectPath RegisterSoftObjectPath;
}
