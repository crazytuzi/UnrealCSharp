#include "Binding/Class/TBindingClassBuilder.inl"
#include "Macro/NamespaceMacro.h"
#if !UE_U_STRUCT_F_PRIMARY_ASSET_ID
#include "Binding/ScriptStruct/TScriptStruct.inl"
#endif

#if UE_U_STRUCT_F_PRIMARY_ASSET_ID
BINDING_STRUCT(FPrimaryAssetId)
#endif

namespace
{
	struct FRegisterPrimaryAssetId
	{
		FRegisterPrimaryAssetId()
		{
			TBindingClassBuilder<FPrimaryAssetId>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FPrimaryAssetId, FPrimaryAssetType, FName),
				             TArray<FString>{"InAssetType", "InAssetName"})
				.Constructor(BINDING_CONSTRUCTOR(FPrimaryAssetId, const FString&),
				             {"TypeAndName"})
				.Property("PrimaryAssetTypeTag", BINDING_READONLY_PROPERTY(&FPrimaryAssetId::PrimaryAssetTypeTag))
				.Property("PrimaryAssetNameTag", BINDING_READONLY_PROPERTY(&FPrimaryAssetId::PrimaryAssetNameTag))
				.Function("ParseTypeAndName",
				          BINDING_OVERLOAD(FPrimaryAssetId(*)(FName), &FPrimaryAssetId::ParseTypeAndName,
				                           TArray<FString>{"TypeAndName"}))
				.Function("ParseTypeAndName",
				          BINDING_OVERLOAD(FPrimaryAssetId(*)(const FString&), &FPrimaryAssetId::ParseTypeAndName,
				                           TArray<FString>{"TypeAndName"}))
				.Function("IsValid", BINDING_FUNCTION(&FPrimaryAssetId::IsValid))
				.Function("ToString", BINDING_FUNCTION(&FPrimaryAssetId::ToString,
				                                       EFunctionInteract::New))
				.Function("FromString", BINDING_FUNCTION(&FPrimaryAssetId::FromString));
		}
	};

	[[maybe_unused]] FRegisterPrimaryAssetId RegisterPrimaryAssetId;
}
