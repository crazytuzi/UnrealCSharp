#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Internationalization/PolyglotTextData.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterPolyglotTextData
{
	FRegisterPolyglotTextData()
	{
		TReflectionClassBuilder<FPolyglotTextData>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FPolyglotTextData, const ELocalizedTextSourceCategory&, const FString&,
			                                 const FString&, const FString&, const FString&)			             ,
			             {"InCategory", "InNamespace", "InKey", "InNativeString", "InNativeCulture"})
			.Function("SetCategory", BINDING_FUNCTION(&FPolyglotTextData::SetCategory),
			          {"InCategory"})
			.Function("GetCategory", BINDING_FUNCTION(&FPolyglotTextData::GetCategory))
			.Function("SetCategory", BINDING_FUNCTION(&FPolyglotTextData::SetNativeCulture),
			          {"InNativeCulture"})
			.Function("GetNativeCulture", BINDING_FUNCTION(&FPolyglotTextData::GetNativeCulture))
			.Function("ResolveNativeCulture", BINDING_FUNCTION(&FPolyglotTextData::ResolveNativeCulture))
			.Function("GetLocalizedCultures", BINDING_FUNCTION(&FPolyglotTextData::GetLocalizedCultures))
			.Function("SetIdentity", BINDING_FUNCTION(&FPolyglotTextData::SetIdentity),
			          {"InNamespace", "InKey"})
			.Function("GetIdentity", BINDING_FUNCTION(&FPolyglotTextData::GetIdentity),
			          {"OutNamespace", "OutKey"})
			.Function("GetNamespace", BINDING_FUNCTION(&FPolyglotTextData::GetNamespace))
			.Function("GetKey", BINDING_FUNCTION(&FPolyglotTextData::GetKey))
			.Function("SetNativeString", BINDING_FUNCTION(&FPolyglotTextData::SetNativeString),
			          {"InNativeString"})
			.Function("GetNativeString", BINDING_FUNCTION(&FPolyglotTextData::GetNativeString))
			.Function("AddLocalizedString", BINDING_FUNCTION(&FPolyglotTextData::AddLocalizedString),
			          {"InCulture", "InLocalizedString"})
			.Function("RemoveLocalizedString", BINDING_FUNCTION(&FPolyglotTextData::RemoveLocalizedString),
			          {"InCulture"})
			.Function("GetLocalizedString", BINDING_FUNCTION(&FPolyglotTextData::GetLocalizedString),
			          {"InCulture", "OutLocalizedString"})
			.Function("ClearLocalizedStrings", BINDING_FUNCTION(&FPolyglotTextData::ClearLocalizedStrings))
			.Function("IsMinimalPatch",
			          BINDING_OVERLOAD(void(FPolyglotTextData::*)(const bool), &FPolyglotTextData::IsMinimalPatch),
			          {"InCulture", "OutLocalizedString"})
			.Function("IsMinimalPatch",
			          BINDING_OVERLOAD(bool(FPolyglotTextData::*)()const, &FPolyglotTextData::IsMinimalPatch))
			.Function("GetText", BINDING_FUNCTION(&FPolyglotTextData::GetText))
			.Register();
	}
};

static FRegisterPolyglotTextData RegisterPolyglotTextData;
