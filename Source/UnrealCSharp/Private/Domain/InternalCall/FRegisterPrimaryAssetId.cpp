#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterPrimaryAssetId
{
	FRegisterPrimaryAssetId()
	{
		TReflectionClassBuilder<FPrimaryAssetId>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FPrimaryAssetId, FPrimaryAssetType, FName),
			             {"InAssetType", "InAssetName"})
			.Constructor(BINDING_CONSTRUCTOR(FPrimaryAssetId, const FString&),
			             {"TypeAndName"})
			.Property("PrimaryAssetTypeTag", BINDING_READONLY_PROPERTY(&FPrimaryAssetId::PrimaryAssetTypeTag))
			.Property("PrimaryAssetNameTag", BINDING_READONLY_PROPERTY(&FPrimaryAssetId::PrimaryAssetNameTag))
			.Function("ParseTypeAndName",
			          BINDING_OVERLOAD(FPrimaryAssetId(*)(FName), &FPrimaryAssetId::ParseTypeAndName),
			          {"TypeAndName"})
			.Function("ParseTypeAndName",
			          BINDING_OVERLOAD(FPrimaryAssetId(*)(const FString&), &FPrimaryAssetId::ParseTypeAndName),
			          {"TypeAndName"})
			.Function("IsValid", BINDING_FUNCTION(&FPrimaryAssetId::IsValid))
			.Function("ToString", BINDING_FUNCTION(&FPrimaryAssetId::ToString),
			          {}, EFunctionInteract::New)
			.Function("FromString", BINDING_FUNCTION(&FPrimaryAssetId::FromString))
			.Register();
	}
};

static FRegisterPrimaryAssetId RegisterPrimaryAssetId;
