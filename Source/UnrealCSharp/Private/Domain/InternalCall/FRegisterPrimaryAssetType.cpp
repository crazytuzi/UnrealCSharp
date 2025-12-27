#include "Binding/Class/TBindingClassBuilder.inl"
#include "Macro/NamespaceMacro.h"
#if !UE_U_STRUCT_F_PRIMARY_ASSET_TYPE
#include "Binding/ScriptStruct/TScriptStruct.inl"
#endif

#if UE_U_STRUCT_F_PRIMARY_ASSET_TYPE
BINDING_STRUCT(FPrimaryAssetType)
#endif

namespace
{
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

	[[maybe_unused]] FRegisterPrimaryAssetType RegisterPrimaryAssetType;
}
