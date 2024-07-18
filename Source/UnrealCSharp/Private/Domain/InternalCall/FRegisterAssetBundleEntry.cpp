#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

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

	FRegisterAssetBundleEntry RegisterAssetBundleEntry;
}
