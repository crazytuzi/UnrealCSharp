﻿#include "Domain/InternalCall/FColorImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterColor
{
	FRegisterColor()
	{
		TReflectionClassBuilder<FColor>(NAMESPACE_LIBRARY)
			.Function("DWColor", FColorImplementation::Color_DWColorImplementation)
			.Function("Equality", FColorImplementation::Color_EqualityImplementation)
			.Function("Inequality", FColorImplementation::Color_InequalityImplementation)
			.Function("FromRGBE", FColorImplementation::Color_FromRGBEImplementation)
			.Function("FromHex", FColorImplementation::Color_FromHexImplementation)
			.Function("MakeRandomColor", FColorImplementation::Color_MakeRandomColorImplementation)
			.Function("MakeRedToGreenColorFromScalar",
			          FColorImplementation::Color_MakeRedToGreenColorFromScalarImplementation)
			.Function("MakeFromColorTemperature", FColorImplementation::Color_MakeFromColorTemperatureImplementation)
			.Function("WithAlpha", FColorImplementation::Color_WithAlphaImplementation)
			.Function("ReinterpretAsLinear", FColorImplementation::Color_ReinterpretAsLinearImplementation)
			.Function("ToHex", FColorImplementation::Color_ToHexImplementation)
			.Function("ToString", FColorImplementation::Color_ToStringImplementation)
			.Function("InitFromString", FColorImplementation::Color_InitFromStringImplementation)
			.Function("ToPackedARGB", FColorImplementation::Color_ToPackedARGBImplementation)
			.Function("ToPackedABGR", FColorImplementation::Color_ToPackedABGRImplementation)
			.Function("ToPackedRGBA", FColorImplementation::Color_ToPackedRGBAImplementation)
			.Function("ToPackedBGRA", FColorImplementation::Color_ToPackedBGRAImplementation)
			.Register();
	}
};

static FRegisterColor RegisterColor;

uint32 FColorImplementation::Color_DWColorImplementation(const MonoObject* InMonoObject)
{
	const auto Color = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(InMonoObject);

	if (Color != nullptr)
	{
		return Color->DWColor();
	}

	return 0u;
}

bool FColorImplementation::Color_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto ColorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(A);

	const auto ColorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(B);

	if (ColorA != nullptr && ColorB != nullptr)
	{
		return ColorA->operator==(*ColorB);
	}

	return false;
}

bool FColorImplementation::Color_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto ColorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(A);

	const auto ColorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(B);

	if (ColorA != nullptr && ColorB != nullptr)
	{
		return ColorA->operator!=(*ColorB);
	}

	return false;
}

void FColorImplementation::Color_FromRGBEImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Color = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (Color != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = Color->FromRGBE();
	}
}

void FColorImplementation::Color_FromHexImplementation(MonoObject* HexString, MonoObject** OutValue)
{
	const auto String = UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
			GetDomain()->Object_To_String(HexString, nullptr)));

	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(NewMonoObject);

	if (String != nullptr && OutColor != nullptr)
	{
		*OutColor = FColor::FromHex(String);
	}
}

void FColorImplementation::Color_MakeRandomColorImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(NewMonoObject);

	if (OutColor != nullptr)
	{
		*OutColor = FColor::MakeRandomColor();
	}
}

void FColorImplementation::Color_MakeRedToGreenColorFromScalarImplementation(const float Scalar, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(NewMonoObject);

	if (OutColor != nullptr)
	{
		*OutColor = FColor::MakeRedToGreenColorFromScalar(Scalar);
	}
}

void FColorImplementation::Color_MakeFromColorTemperatureImplementation(const float Temp, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(NewMonoObject);

	if (OutColor != nullptr)
	{
		*OutColor = FColor::MakeFromColorTemperature(Temp);
	}
}

void FColorImplementation::Color_WithAlphaImplementation(const MonoObject* InMonoObject, const uint8 Alpha,
                                                         MonoObject** OutValue)
{
	const auto Color = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(NewMonoObject);

	if (Color != nullptr && OutColor != nullptr)
	{
		*OutColor = Color->WithAlpha(Alpha);
	}
}

void FColorImplementation::Color_ReinterpretAsLinearImplementation(const MonoObject* InMonoObject,
                                                                   MonoObject** OutValue)
{
	const auto Color = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (Color != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = Color->ReinterpretAsLinear();
	}
}

void FColorImplementation::Color_ToHexImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Color = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(InMonoObject);

	if (Color != nullptr)
	{
		const auto ResultString = Color->ToHex();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FColorImplementation::Color_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Color = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(InMonoObject);

	if (Color != nullptr)
	{
		const auto ResultString = Color->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FColorImplementation::Color_InitFromStringImplementation(const MonoObject* InMonoObject,
                                                              MonoObject* InSourceString)
{
	const auto Color = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(InMonoObject);

	if (Color != nullptr && InSourceString != nullptr)
	{
		return Color->InitFromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InSourceString, nullptr))));
	}

	return false;
}

uint32 FColorImplementation::Color_ToPackedARGBImplementation(const MonoObject* InMonoObject)
{
	const auto Color = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(InMonoObject);

	if (Color != nullptr)
	{
		return Color->ToPackedARGB();
	}

	return 0u;
}

uint32 FColorImplementation::Color_ToPackedABGRImplementation(const MonoObject* InMonoObject)
{
	const auto Color = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(InMonoObject);

	if (Color != nullptr)
	{
		return Color->ToPackedABGR();
	}

	return 0u;
}

uint32 FColorImplementation::Color_ToPackedRGBAImplementation(const MonoObject* InMonoObject)
{
	const auto Color = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(InMonoObject);

	if (Color != nullptr)
	{
		return Color->ToPackedRGBA();
	}

	return 0u;
}

uint32 FColorImplementation::Color_ToPackedBGRAImplementation(const MonoObject* InMonoObject)
{
	const auto Color = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(InMonoObject);

	if (Color != nullptr)
	{
		return Color->ToPackedBGRA();
	}

	return 0u;
}
