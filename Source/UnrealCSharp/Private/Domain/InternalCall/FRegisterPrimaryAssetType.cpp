#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

#ifdef _MSC_VER
#pragma warning (push)

#pragma warning (disable: 5103)
#endif

struct FRegisterPrimaryAssetType
{
	FRegisterPrimaryAssetType()
	{
		TBindingClassBuilder<FPrimaryAssetType>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FPrimaryAssetType, FName),
			             TArray<FString>{"InName"})
			.Function("GetName", BINDING_FUNCTION(&FPrimaryAssetType::GetName))
			.Function("IsValid", BINDING_FUNCTION(&FPrimaryAssetType::IsValid))
			.Function("ToString", BINDING_FUNCTION(&FPrimaryAssetType::ToString,
			                                       EFunctionInteract::New));
	}
};

static FRegisterPrimaryAssetType RegisterPrimaryAssetType;

#ifdef _MSC_VER
#pragma warning (pop)
#endif
