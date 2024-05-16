#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

#ifdef _MSC_VER
#pragma warning (push)

#pragma warning (disable: 5103)
#endif

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

static FRegisterAssetBundleEntry RegisterAssetBundleEntry;

#ifdef _MSC_VER
#pragma warning (pop)
#endif
