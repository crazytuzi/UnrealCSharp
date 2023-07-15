#include "Domain/InternalCall/FLinearColorImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStructPropertyClass.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterLinearColor
{
	FRegisterLinearColor()
	{
		TReflectionClassBuilder<FLinearColor>(NAMESPACE_LIBRARY)
			.Function("ToRGBE", static_cast<void*>(FLinearColorImplementation::LinearColor_ToRGBEImplementation))
			.Function("FromSRGBColor",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_FromSRGBColorImplementation))
			.Function("FromPow22Color",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_FromPow22ColorImplementation))
			.Function("Component", static_cast<void*>(FLinearColorImplementation::LinearColor_ComponentImplementation))
			.Function("Add", static_cast<void*>(FLinearColorImplementation::LinearColor_AddImplementation))
			.Function("Subtract", static_cast<void*>(FLinearColorImplementation::LinearColor_SubtractImplementation))
			.Function("Multiply", static_cast<void*>(FLinearColorImplementation::LinearColor_MultiplyImplementation))
			.Function("MultiplyScalar",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_MultiplyScalarImplementation))
			.Function("Divide", static_cast<void*>(FLinearColorImplementation::LinearColor_DivideImplementation))
			.Function("DivideScalar",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_DivideScalarImplementation))
			.Function("GetClamped",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_GetClampedImplementation))
			.Function("Equality", static_cast<void*>(FLinearColorImplementation::LinearColor_EqualityImplementation))
			.Function("Inequality",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_InequalityImplementation))
			.Function("Equals", static_cast<void*>(FLinearColorImplementation::LinearColor_EqualsImplementation))
			.Function("CopyWithNewOpacity",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_CopyWithNewOpacityImplementation))
			.Function("MakeFromHSV8",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_MakeFromHSV8Implementation))
			.Function("MakeRandomColor",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_MakeRandomColorImplementation))
			.Function("MakeFromColorTemperature",
			          static_cast<void*>(
				          FLinearColorImplementation::LinearColor_MakeFromColorTemperatureImplementation))
			.Function("Dist", static_cast<void*>(FLinearColorImplementation::LinearColor_DistImplementation))
			.Function("LinearRGBToHSV",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_LinearRGBToHSVImplementation))
			.Function("HSVToLinearRGB",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_HSVToLinearRGBImplementation))
			.Function("LerpUsingHSV",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_LerpUsingHSVImplementation))
#if UE_LINEAR_COLOR_QUANTIZE_FLOOR
			.Function("QuantizeFloor",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_QuantizeFloorImplementation))
#endif
			.Function("Quantize", static_cast<void*>(FLinearColorImplementation::LinearColor_QuantizeImplementation))
			.Function("QuantizeRound",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_QuantizeRoundImplementation))
			.Function("ToFColor", static_cast<void*>(FLinearColorImplementation::LinearColor_ToFColorImplementation))
			.Function("Desaturate",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_DesaturateImplementation))
#if UE_LINEAR_COLOR_COMPUTE_LUMINANCE
			.Function("ComputeLuminance",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_ComputeLuminanceImplementation))
#endif
			.Function("GetMax", static_cast<void*>(FLinearColorImplementation::LinearColor_GetMaxImplementation))
			.Function("IsAlmostBlack",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_IsAlmostBlackImplementation))
			.Function("GetMin", static_cast<void*>(FLinearColorImplementation::LinearColor_GetMinImplementation))
			.Function("GetLuminance",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_GetLuminanceImplementation))
			.Function("ToString", static_cast<void*>(FLinearColorImplementation::LinearColor_ToStringImplementation))
			.Function("InitFromString",
			          static_cast<void*>(FLinearColorImplementation::LinearColor_InitFromStringImplementation))
			.Register();
	}
};

static FRegisterLinearColor RegisterLinearColor;

void FLinearColorImplementation::LinearColor_ToRGBEImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(NewMonoObject);

	if (LinearColor != nullptr && OutColor != nullptr)
	{
		*OutColor = LinearColor->ToRGBE();
	}
}

void FLinearColorImplementation::LinearColor_FromSRGBColorImplementation(const MonoObject* Color, MonoObject** OutValue)
{
	const auto InColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(Color);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (InColor != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = FLinearColor::FromSRGBColor(*InColor);
	}
}

void FLinearColorImplementation::LinearColor_FromPow22ColorImplementation(
	const MonoObject* Color, MonoObject** OutValue)
{
	const auto InColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(Color);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (InColor != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = FLinearColor::FromPow22Color(*InColor);
	}
}

float FLinearColorImplementation::LinearColor_ComponentImplementation(const MonoObject* InMonoObject, const int32 Index)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	if (LinearColor != nullptr)
	{
		return LinearColor->Component(Index);
	}

	return 0.f;
}

void FLinearColorImplementation::LinearColor_AddImplementation(const MonoObject* A, const MonoObject* B,
                                                               MonoObject** OutValue)
{
	const auto LinearColorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(A);

	const auto LinearColorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(B);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (LinearColorA != nullptr && LinearColorB != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = LinearColorA->operator+(*LinearColorB);
	}
}

void FLinearColorImplementation::LinearColor_SubtractImplementation(const MonoObject* A, const MonoObject* B,
                                                                    MonoObject** OutValue)
{
	const auto LinearColorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(A);

	const auto LinearColorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(B);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (LinearColorA != nullptr && LinearColorB != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = LinearColorA->operator-(*LinearColorB);
	}
}

void FLinearColorImplementation::LinearColor_MultiplyImplementation(const MonoObject* A, const MonoObject* B,
                                                                    MonoObject** OutValue)
{
	const auto LinearColorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(A);

	const auto LinearColorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(B);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (LinearColorA != nullptr && LinearColorB != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = LinearColorA->operator*(*LinearColorB);
	}
}

void FLinearColorImplementation::LinearColor_MultiplyScalarImplementation(
	const MonoObject* InMonoObject, const float Scalar, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (LinearColor != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = LinearColor->operator*(Scalar);
	}
}

void FLinearColorImplementation::LinearColor_DivideImplementation(const MonoObject* A, const MonoObject* B,
                                                                  MonoObject** OutValue)
{
	const auto LinearColorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(A);

	const auto LinearColorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(B);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (LinearColorA != nullptr && LinearColorB != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = LinearColorA->operator/(*LinearColorB);
	}
}

void FLinearColorImplementation::LinearColor_DivideScalarImplementation(const MonoObject* InMonoObject,
                                                                        const float Scalar, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (LinearColor != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = LinearColor->operator/(Scalar);
	}
}

void FLinearColorImplementation::LinearColor_GetClampedImplementation(const MonoObject* InMonoObject, const float InMin,
                                                                      const float InMax, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (LinearColor != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = LinearColor->GetClamped(InMin, InMax);
	}
}

bool FLinearColorImplementation::LinearColor_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto LinearColorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(A);

	const auto LinearColorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(B);

	if (LinearColorA != nullptr && LinearColorB != nullptr)
	{
		return LinearColorA->operator==(*LinearColorB);
	}

	return false;
}

bool FLinearColorImplementation::LinearColor_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto LinearColorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(A);

	const auto LinearColorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(B);

	if (LinearColorA != nullptr && LinearColorB != nullptr)
	{
		return LinearColorA->operator!=(*LinearColorB);
	}

	return false;
}

bool FLinearColorImplementation::LinearColor_EqualsImplementation(const MonoObject* A, const MonoObject* B,
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
	const MonoObject* InMonoObject, const float NewOpacicty, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (LinearColor != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = LinearColor->CopyWithNewOpacity(NewOpacicty);
	}
}

void FLinearColorImplementation::LinearColor_MakeFromHSV8Implementation(const uint8 H, const uint8 S, const uint8 V,
                                                                        MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (OutLinearColor != nullptr)
	{
		*OutLinearColor = FLinearColor::MakeFromHSV8(H, S, V);
	}
}

void FLinearColorImplementation::LinearColor_MakeRandomColorImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (OutLinearColor != nullptr)
	{
		*OutLinearColor = FLinearColor::MakeRandomColor();
	}
}

void FLinearColorImplementation::LinearColor_MakeFromColorTemperatureImplementation(
	const float Temp, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (OutLinearColor != nullptr)
	{
		*OutLinearColor = FLinearColor::MakeFromColorTemperature(Temp);
	}
}

float FLinearColorImplementation::LinearColor_DistImplementation(const MonoObject* V1, const MonoObject* V2)
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
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (OutLinearColor != nullptr)
	{
		*OutLinearColor = LinearColor->LinearRGBToHSV();
	}
}

void FLinearColorImplementation::LinearColor_HSVToLinearRGBImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (OutLinearColor != nullptr)
	{
		*OutLinearColor = LinearColor->HSVToLinearRGB();
	}
}

void FLinearColorImplementation::LinearColor_LerpUsingHSVImplementation(const MonoObject* From, const MonoObject* To,
                                                                        const float Progress, MonoObject** OutValue)
{
	const auto LinearColorFrom = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(From);

	const auto LinearColorTo = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(To);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (LinearColorFrom != nullptr && LinearColorTo != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = FLinearColor::LerpUsingHSV(*LinearColorFrom, *LinearColorTo, Progress);
	}
}

#if UE_LINEAR_COLOR_QUANTIZE_FLOOR
void FLinearColorImplementation::LinearColor_QuantizeFloorImplementation(const MonoObject* InMonoObject,
                                                                         MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(NewMonoObject);

	if (LinearColor != nullptr && OutColor != nullptr)
	{
		*OutColor = LinearColor->QuantizeFloor();
	}
}
#endif

void FLinearColorImplementation::LinearColor_QuantizeImplementation(const MonoObject* InMonoObject,
                                                                    MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(NewMonoObject);

	if (LinearColor != nullptr && OutColor != nullptr)
	{
		*OutColor = LinearColor->Quantize();
	}
}

void FLinearColorImplementation::LinearColor_QuantizeRoundImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(NewMonoObject);

	if (LinearColor != nullptr && OutColor != nullptr)
	{
		*OutColor = LinearColor->QuantizeRound();
	}
}

void FLinearColorImplementation::LinearColor_ToFColorImplementation(const MonoObject* InMonoObject, const bool bSRGB,
                                                                    MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FColor, FColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FColor>(NewMonoObject);

	if (LinearColor != nullptr && OutColor != nullptr)
	{
		*OutColor = LinearColor->ToFColor(bSRGB);
	}
}

void FLinearColorImplementation::LinearColor_DesaturateImplementation(const MonoObject* InMonoObject,
                                                                      const float Desaturation, MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FLinearColor, FLinearColor>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutLinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FLinearColor>(
		NewMonoObject);

	if (LinearColor != nullptr && OutLinearColor != nullptr)
	{
		*OutLinearColor = LinearColor->Desaturate(Desaturation);
	}
}

#if UE_LINEAR_COLOR_COMPUTE_LUMINANCE
float FLinearColorImplementation::LinearColor_ComputeLuminanceImplementation(const MonoObject* InMonoObject)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	if (LinearColor != nullptr)
	{
		return LinearColor->ComputeLuminance();
	}

	return 0.f;
}
#endif

float FLinearColorImplementation::LinearColor_GetMaxImplementation(const MonoObject* InMonoObject)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	if (LinearColor != nullptr)
	{
		return LinearColor->GetMax();
	}

	return 0.f;
}

bool FLinearColorImplementation::LinearColor_IsAlmostBlackImplementation(const MonoObject* InMonoObject)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	if (LinearColor != nullptr)
	{
		return LinearColor->IsAlmostBlack();
	}

	return false;
}

float FLinearColorImplementation::LinearColor_GetMinImplementation(const MonoObject* InMonoObject)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	if (LinearColor != nullptr)
	{
		return LinearColor->GetMin();
	}

	return 0.f;
}

float FLinearColorImplementation::LinearColor_GetLuminanceImplementation(const MonoObject* InMonoObject)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	if (LinearColor != nullptr)
	{
		return LinearColor->GetLuminance();
	}

	return 0.f;
}

void FLinearColorImplementation::LinearColor_ToStringImplementation(const MonoObject* InMonoObject,
                                                                    MonoObject** OutValue)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	if (LinearColor != nullptr)
	{
		const auto ResultString = LinearColor->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FLinearColorImplementation::LinearColor_InitFromStringImplementation(
	const MonoObject* InMonoObject, MonoObject* InSourceString)
{
	const auto LinearColor = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FLinearColor>(InMonoObject);

	if (LinearColor != nullptr && InSourceString != nullptr)
	{
		return LinearColor->InitFromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InSourceString, nullptr))));
	}

	return false;
}
