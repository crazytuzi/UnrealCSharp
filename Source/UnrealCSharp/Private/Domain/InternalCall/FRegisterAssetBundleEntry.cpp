#include "Binding/Class/TBindingClassBuilder.inl"
#include "Macro/NamespaceMacro.h"
#if !UE_U_STRUCT_F_ASSET_BUNDLE_ENTRY
#include "Binding/ScriptStruct/TScriptStruct.inl"
#endif

#if UE_U_STRUCT_F_ASSET_BUNDLE_ENTRY
BINDING_STRUCT(FAssetBundleEntry)
#endif

namespace
{
	struct FRegisterAssetBundleEntry
	{
		FRegisterAssetBundleEntry()
		{
			TBindingClassBuilder<FAssetBundleEntry>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FAssetBundleEntry, const FAssetBundleEntry&),
				             TArray<FString>{"OldEntry"})
				.Constructor(BINDING_CONSTRUCTOR(FAssetBundleEntry, FName),
				             TArray<FString>{"InBundleName"})
				.Function("IsValid", BINDING_FUNCTION(&FAssetBundleEntry::IsValid));
		}
	};

	[[maybe_unused]] FRegisterAssetBundleEntry RegisterAssetBundleEntry;
}
