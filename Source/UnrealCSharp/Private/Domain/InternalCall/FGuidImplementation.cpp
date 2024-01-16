﻿#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/Enum/TBindingEnumBuilder.inl"
#include "Macro/NamespaceMacro.h"
#include "UEVersion.h"

BINDING_ENGINE_ENUM(EGuidFormats)

struct FRegisterGuidFormats
{
	FRegisterGuidFormats()
	{
		TBindingEnumBuilder<EGuidFormats>()
			.Enumerator("Digits", EGuidFormats::Digits)
			.Enumerator("DigitsWithHyphens", EGuidFormats::DigitsWithHyphens)
			.Enumerator("DigitsWithHyphensLower", EGuidFormats::DigitsWithHyphensLower)
			.Enumerator("DigitsWithHyphensInBraces", EGuidFormats::DigitsWithHyphensInBraces)
			.Enumerator("DigitsWithHyphensInParentheses", EGuidFormats::DigitsWithHyphensInParentheses)
			.Enumerator("HexValuesInBraces", EGuidFormats::HexValuesInBraces)
			.Enumerator("UniqueObjectGuid", EGuidFormats::UniqueObjectGuid)
			.Enumerator("Short", EGuidFormats::Short)
			.Enumerator("Base36Encoded", EGuidFormats::Base36Encoded)
			.Register();
	}
};

static FRegisterGuidFormats RegisterGuidFormats;

struct FRegisterGuid
{
	static bool GreaterThanImplementation(const FGuid& X, const FGuid& Y)
	{
		return	((X.A < Y.A) ? true : ((X.A > Y.A) ? false :
				((X.B < Y.B) ? true : ((X.B > Y.B) ? false :
				((X.C < Y.C) ? true : ((X.C > Y.C) ? false :
				((X.D < Y.D) ? true : ((X.D > Y.D) ? false : false))))))));
	}

	static FString LexToStringImplementation(const FGuid& Value)
	{
		return LexToString(Value);
	}

	FRegisterGuid()
	{
		TReflectionClassBuilder<FGuid>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FGuid, uint32, uint32, uint32, uint32),
			             {"InA", "InB", "InC", "InD"})
			.Constructor(BINDING_CONSTRUCTOR(FGuid, const FString&),
			             {"InGuidStr"})
			.Less()
			.Subscript(BINDING_SUBSCRIPT(FGuid, uint32, int32),
			           {"Index"})
			.Function("operator >", FUNCTION_GREATER, BINDING_FUNCTION(&GreaterThanImplementation))
			.Function("LexToString", BINDING_FUNCTION(&LexToStringImplementation),
			          {"Value"})
			.Function("Invalidate", BINDING_FUNCTION(&FGuid::Invalidate))
			.Function("IsValid", BINDING_FUNCTION(&FGuid::IsValid))
#if UE_GUID_TO_STRING
			.Function("ToString", BINDING_OVERLOAD(FString(FGuid::*)()const, &FGuid::ToString))
#endif
			.Function("ToString", BINDING_OVERLOAD(FString(FGuid::*)(EGuidFormats)const, &FGuid::ToString),
			          {"Format"})
			.Function("NewGuid", BINDING_FUNCTION(&FGuid::NewGuid))
			.Function("Parse", BINDING_FUNCTION(&FGuid::Parse))
			.Function("ParseExact", BINDING_FUNCTION(&FGuid::ParseExact))
			.Register();
	}
};

static FRegisterGuid RegisterGuid;
