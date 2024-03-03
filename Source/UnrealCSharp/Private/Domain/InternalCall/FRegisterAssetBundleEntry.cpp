#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterAssetBundleEntry
{
	FRegisterAssetBundleEntry()
	{
		TBindingClassBuilder<FAssetBundleEntry>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FAssetBundleEntry, const FAssetBundleEntry&),
			             {"OldEntry"})
			.Constructor(BINDING_CONSTRUCTOR(FAssetBundleEntry, FName),
			             {"InBundleName"})
			.Function("IsValid", BINDING_FUNCTION(&FAssetBundleEntry::IsValid))
			.Register();
	}
};

static FRegisterAssetBundleEntry RegisterAssetBundleEntry;
