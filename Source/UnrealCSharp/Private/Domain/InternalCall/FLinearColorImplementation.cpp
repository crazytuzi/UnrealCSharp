#include "Domain/InternalCall/FLinearColorImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterLinearColor
{
	FRegisterLinearColor()
	{
		TReflectionClassBuilder<FLinearColor>(NAMESPACE_LIBRARY)
			.Function("ToRGBE", FLinearColorImplementation::LinearColor_ToRGBEImplementation)
			.Function("FromSRGBColor", FLinearColorImplementation::LinearColor_FromSRGBColorImplementation)
			.Function("FromPow22Color", FLinearColorImplementation::LinearColor_FromPow22ColorImplementation)
			.Function("Component", FLinearColorImplementation::LinearColor_ComponentImplementation)
			.Function("Add", FLinearColorImplementation::LinearColor_AddImplementation)
			.Function("Subtract", FLinearColorImplementation::LinearColor_SubtractImplementation)
			.Function("Multiply", FLinearColorImplementation::LinearColor_MultiplyImplementation)
			.Function("MultiplyScalar", FLinearColorImplementation::LinearColor_MultiplyScalarImplementation)
			.Function("Divide", FLinearColorImplementation::LinearColor_DivideImplementation)
			.Function("DivideScalar", FLinearColorImplementation::LinearColor_DivideScalarImplementation)
			.Function("GetClamped", FLinearColorImplementation::LinearColor_GetClampedImplementation)
			.Function("Equals", FLinearColorImplementation::LinearColor_EqualsImplementation)
			.Function("CopyWithNewOpacity", FLinearColorImplementation::LinearColor_CopyWithNewOpacityImplementation)
			.Function("MakeFromHSV8", FLinearColorImplementation::LinearColor_MakeFromHSV8Implementation)
			.Function("MakeRandomColor", FLinearColorImplementation::LinearColor_MakeRandomColorImplementation)
			.Function("MakeFromColorTemperature",
			          FLinearColorImplementation::LinearColor_MakeFromColorTemperatureImplementation)
			.Function("Dist", FLinearColorImplementation::LinearColor_DistImplementation)
			.Function("LinearRGBToHSV", FLinearColorImplementation::LinearColor_LinearRGBToHSVImplementation)
			.Function("HSVToLinearRGB", FLinearColorImplementation::LinearColor_HSVToLinearRGBImplementation)
			.Function("LerpUsingHSV", FLinearColorImplementation::LinearColor_LerpUsingHSVImplementation)
#if UE_LINEAR_COLOR_QUANTIZE_FLOOR
			.Function("QuantizeFloor", FLinearColorImplementation::LinearColor_QuantizeFloorImplementation)
#endif
			.Function("Quantize", FLinearColorImplementation::LinearColor_QuantizeImplementation)
			.Function("QuantizeRound", FLinearColorImplementation::LinearColor_QuantizeRoundImplementation)
			.Function("ToFColor", FLinearColorImplementation::LinearColor_ToFColorImplementation)
			.Function("Desaturate", FLinearColorImplementation::LinearColor_DesaturateImplementation)
#if UE_LINEAR_COLOR_COMPUTE_LUMINANCE
			.Function("ComputeLuminance", FLinearColorImplementation::LinearColor_ComputeLuminanceImplementation)
#endif
			.Function("GetMax", FLinearColorImplementation::LinearColor_GetMaxImplementation)
			.Function("IsAlmostBlack", FLinearColorImplementation::LinearColor_IsAlmostBlackImplementation)
			.Function("GetMin", FLinearColorImplementation::LinearColor_GetMinImplementation)
			.Function("GetLuminance", FLinearColorImplementation::LinearColor_GetLuminanceImplementation)
			.Function("ToString", FLinearColorImplementation::LinearColor_ToStringImplementation)
			.Function("InitFromString", FLinearColorImplementation::LinearColor_InitFromStringImplementation)
			.Register();
	}
};

static FRegisterLinearColor RegisterLinearColor;

void FLinearColorImplementation::LinearColor_ToRGBEImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = new FColor(LinearColor->ToRGBE());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FColor>::Get(), OutColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_FromSRGBColorImplementation(const MonoObject* Color, MonoObject** OutValue)
{
	const auto InColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(Color);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(FLinearColor::FromSRGBColor(*InColor));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_FromPow22ColorImplementation(
	const MonoObject* Color, MonoObject** OutValue)
{
	const auto InColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(Color);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(FLinearColor::FromPow22Color(*InColor));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

float FLinearColorImplementation::LinearColor_ComponentImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const int32 Index)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	if (LinearColor != nullptr)
	{
		return LinearColor->Component(Index);
	}

	return 0.f;
}

void FLinearColorImplementation::LinearColor_AddImplementation(const FGarbageCollectionHandle A,
                                                               const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto LinearColorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(A);

	const auto LinearColorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(B);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(LinearColorA->operator+(*LinearColorB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_SubtractImplementation(const FGarbageCollectionHandle A,
                                                                    const FGarbageCollectionHandle B,
                                                                    MonoObject** OutValue)
{
	const auto LinearColorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(A);

	const auto LinearColorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(B);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(LinearColorA->operator-(*LinearColorB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_MultiplyImplementation(const FGarbageCollectionHandle A,
                                                                    const FGarbageCollectionHandle B,
                                                                    MonoObject** OutValue)
{
	const auto LinearColorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(A);

	const auto LinearColorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(B);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(LinearColorA->operator*(*LinearColorB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_MultiplyScalarImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const float Scalar, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(LinearColor->operator*(Scalar));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_DivideImplementation(const FGarbageCollectionHandle A,
                                                                  const FGarbageCollectionHandle B,
                                                                  MonoObject** OutValue)
{
	const auto LinearColorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(A);

	const auto LinearColorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(B);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(LinearColorA->operator/(*LinearColorB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_DivideScalarImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const float Scalar, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(LinearColor->operator/(Scalar));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_GetClampedImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const float InMin, const float InMax,
	MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(LinearColor->GetClamped(InMin, InMax));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

bool FLinearColorImplementation::LinearColor_EqualsImplementation(const FGarbageCollectionHandle A,
                                                                  const FGarbageCollectionHandle B,
                                                                  const float Tolerance)
{
	const auto LinearColorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(A);

	const auto LinearColorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(B);

	if (LinearColorA != nullptr && LinearColorB != nullptr)
	{
		return LinearColorA->Equals(*LinearColorB, Tolerance);
	}

	return false;
}

void FLinearColorImplementation::LinearColor_CopyWithNewOpacityImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const float NewOpacicty, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(LinearColor->CopyWithNewOpacity(NewOpacicty));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_MakeFromHSV8Implementation(const uint8 H, const uint8 S, const uint8 V,
                                                                        MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(FLinearColor::MakeFromHSV8(H, S, V));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_MakeRandomColorImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(FLinearColor::MakeRandomColor());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_MakeFromColorTemperatureImplementation(
	const float Temp, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(FLinearColor::MakeFromColorTemperature(Temp));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

float FLinearColorImplementation::LinearColor_DistImplementation(const FGarbageCollectionHandle V1,
                                                                 const FGarbageCollectionHandle V2)
{
	const auto LinearColorV1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(V1);

	const auto LinearColorV2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(V2);

	if (LinearColorV1 != nullptr && LinearColorV2 != nullptr)
	{
		return FLinearColor::Dist(*LinearColorV1, *LinearColorV2);
	}

	return 0.f;
}

void FLinearColorImplementation::LinearColor_LinearRGBToHSVImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(LinearColor->LinearRGBToHSV());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_HSVToLinearRGBImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(LinearColor->HSVToLinearRGB());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_LerpUsingHSVImplementation(const MonoObject* From, const MonoObject* To,
                                                                        const float Progress, MonoObject** OutValue)
{
	const auto LinearColorFrom = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(From);

	const auto LinearColorTo = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(To);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new
		FLinearColor(FLinearColor::LerpUsingHSV(*LinearColorFrom, *LinearColorTo, Progress));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

#if UE_LINEAR_COLOR_QUANTIZE_FLOOR
void FLinearColorImplementation::LinearColor_QuantizeFloorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = new FColor(LinearColor->QuantizeFloor());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FColor>::Get(), OutColor, NewMonoObject);
}
#endif

void FLinearColorImplementation::LinearColor_QuantizeImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = new FColor(LinearColor->Quantize());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FColor>::Get(), OutColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_QuantizeRoundImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = new FColor(LinearColor->QuantizeRound());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FColor>::Get(), OutColor,
	                                                        NewMonoObject);
}

void FLinearColorImplementation::LinearColor_ToFColorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const bool bSRGB, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = new FColor(LinearColor->ToFColor(bSRGB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FColor>::Get(), OutColor, NewMonoObject);
}

void FLinearColorImplementation::LinearColor_DesaturateImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const float Desaturation, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = new FLinearColor(LinearColor->Desaturate(Desaturation));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FLinearColor>::Get(), OutLinearColor,
	                                                        NewMonoObject);
}

#if UE_LINEAR_COLOR_COMPUTE_LUMINANCE
float FLinearColorImplementation::LinearColor_ComputeLuminanceImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	if (LinearColor != nullptr)
	{
		return LinearColor->ComputeLuminance();
	}

	return 0.f;
}
#endif

float FLinearColorImplementation::LinearColor_GetMaxImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	if (LinearColor != nullptr)
	{
		return LinearColor->GetMax();
	}

	return 0.f;
}

bool FLinearColorImplementation::LinearColor_IsAlmostBlackImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	if (LinearColor != nullptr)
	{
		return LinearColor->IsAlmostBlack();
	}

	return false;
}

float FLinearColorImplementation::LinearColor_GetMinImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	if (LinearColor != nullptr)
	{
		return LinearColor->GetMin();
	}

	return 0.f;
}

float FLinearColorImplementation::LinearColor_GetLuminanceImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	if (LinearColor != nullptr)
	{
		return LinearColor->GetLuminance();
	}

	return 0.f;
}

void FLinearColorImplementation::LinearColor_ToStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	if (LinearColor != nullptr)
	{
		const auto ResultString = LinearColor->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FLinearColorImplementation::LinearColor_InitFromStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InSourceString)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InGarbageCollectionHandle);

	if (LinearColor != nullptr && InSourceString != nullptr)
	{
		return LinearColor->InitFromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InSourceString, nullptr))));
	}

	return false;
}
