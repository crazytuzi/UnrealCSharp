#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterAssetBundleEntry
{
	FRegisterAssetBundleEntry()
	{
		TReflectionClassBuilder<FAssetBundleEntry>(NAMESPACE_BINDING)
			.Function("IsValid", BINDING_FUNCTION(&FAssetBundleEntry::IsValid))
			.Register();
	}
};

static FRegisterAssetBundleEntry RegisterAssetBundleEntry;
