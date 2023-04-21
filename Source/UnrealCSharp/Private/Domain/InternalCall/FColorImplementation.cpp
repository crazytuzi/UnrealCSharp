#include "Domain/InternalCall/FColorImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterColor
{
	FRegisterColor()
	{
		TScriptStructBuilder<FColor>(NAMESPACE_LIBRARY)
			.Function("DWColor", static_cast<void*>(FColorImplementation::Color_DWColorImplementation))
			.Function("Equality", static_cast<void*>(FColorImplementation::Color_EqualityImplementation))
			.Function("Inequality", static_cast<void*>(FColorImplementation::Color_InequalityImplementation))
			.Function("FromRGBE", static_cast<void*>(FColorImplementation::Color_FromRGBEImplementation))
			.Function("FromHex", static_cast<void*>(FColorImplementation::Color_FromHexImplementation))
			.Function("MakeRandomColor", static_cast<void*>(FColorImplementation::Color_MakeRandomColorImplementation))
			.Function("MakeRedToGreenColorFromScalar",
			          static_cast<void*>(FColorImplementation::Color_MakeRedToGreenColorFromScalarImplementation))
			.Function("MakeFromColorTemperature",
			          static_cast<void*>(FColorImplementation::Color_MakeFromColorTemperatureImplementation))
			.Function("WithAlpha", static_cast<void*>(FColorImplementation::Color_WithAlphaImplementation))
			.Function("ReinterpretAsLinear",
			          static_cast<void*>(FColorImplementation::Color_ReinterpretAsLinearImplementation))
			.Function("ToHex", static_cast<void*>(FColorImplementation::Color_ToHexImplementation))
			.Function("ToString", static_cast<void*>(FColorImplementation::Color_ToStringImplementation))
			.Function("InitFromString", static_cast<void*>(FColorImplementation::Color_InitFromStringImplementation))
			.Function("ToPackedARGB", static_cast<void*>(FColorImplementation::Color_ToPackedARGBImplementation))
			.Function("ToPackedABGR", static_cast<void*>(FColorImplementation::Color_ToPackedABGRImplementation))
			.Function("ToPackedRGBA", static_cast<void*>(FColorImplementation::Color_ToPackedRGBAImplementation))
			.Function("ToPackedBGRA", static_cast<void*>(FColorImplementation::Color_ToPackedBGRAImplementation))
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

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FLinearColor)),
		CLASS_SCRIPT_STRUCT_NAME(FLinearColor));

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

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FColor)),
		CLASS_SCRIPT_STRUCT_NAME(FColor));

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
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FColor)),
		CLASS_SCRIPT_STRUCT_NAME(FColor));

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
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FColor)),
		CLASS_SCRIPT_STRUCT_NAME(FColor));

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
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FColor)),
		CLASS_SCRIPT_STRUCT_NAME(FColor));

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

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FColor)),
		CLASS_SCRIPT_STRUCT_NAME(FColor));

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

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FLinearColor)),
		CLASS_SCRIPT_STRUCT_NAME(FLinearColor));

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

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

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

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

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
