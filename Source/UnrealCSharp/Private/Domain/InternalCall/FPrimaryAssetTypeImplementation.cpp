#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterPrimaryAssetType
{
	FRegisterPrimaryAssetType()
	{
		TReflectionClassBuilder<FPrimaryAssetType>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FPrimaryAssetType, FName),
			             {"InName"})
			.Function("GetName", BINDING_FUNCTION(&FPrimaryAssetType::GetName))
			.Function("IsValid", BINDING_FUNCTION(&FPrimaryAssetType::IsValid))
			.Function("ToString", BINDING_FUNCTION(&FPrimaryAssetType::ToString))
			.Register();
	}
};

static FRegisterPrimaryAssetType RegisterPrimaryAssetType;
