#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"
#include "FRegisterForceInit.h"

namespace
{
	struct FRegisterLinearColor
	{
		static FLinearColor MultipliesImplementation(const FLinearColor& In, const float Scalar)
		{
			return &In != nullptr ? In * Scalar : decltype(In * Scalar)();
		}

		static FLinearColor DividesImplementation(const FLinearColor& In, const float Scalar)
		{
			return &In != nullptr ? In / Scalar : decltype(In / Scalar)();
		}

		FRegisterLinearColor()
		{
			TBindingClassBuilder<FLinearColor>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FLinearColor, EForceInit))
				.Constructor(BINDING_CONSTRUCTOR(FLinearColor, float, float, float, float),
				             TArray<FString>{"InR", "InG", "InB", "InA"})
				.Constructor(BINDING_CONSTRUCTOR(FLinearColor, const FColor&),
				             TArray<FString>{"Color"})
				.Plus()
				.Minus()
				.Multiplies()
				.Divides()
				.Function("operator *", FUNCTION_MULTIPLIES, BINDING_FUNCTION(&MultipliesImplementation))
				.Function("operator /", FUNCTION_DIVIDES, BINDING_FUNCTION(&DividesImplementation))
				.Property("White", BINDING_READONLY_PROPERTY(&FLinearColor::White))
				.Property("Gray", BINDING_READONLY_PROPERTY(&FLinearColor::Gray))
				.Property("Black", BINDING_READONLY_PROPERTY(&FLinearColor::Black))
				.Property("Transparent", BINDING_READONLY_PROPERTY(&FLinearColor::Transparent))
				.Property("Red", BINDING_READONLY_PROPERTY(&FLinearColor::Red))
				.Property("Green", BINDING_READONLY_PROPERTY(&FLinearColor::Green))
				.Property("Blue", BINDING_READONLY_PROPERTY(&FLinearColor::Blue))
				.Property("Yellow", BINDING_READONLY_PROPERTY(&FLinearColor::Yellow))
				.Function("ToRGBE", BINDING_FUNCTION(&FLinearColor::ToRGBE))
				.Function("FromSRGBColor", BINDING_FUNCTION(&FLinearColor::FromSRGBColor,
				                                            TArray<FString>{"Color"}))
				.Function("FromPow22Color", BINDING_FUNCTION(&FLinearColor::FromPow22Color,
				                                             TArray<FString>{"Color"}))
				.Function("Component",
				          BINDING_OVERLOAD(const float&(FLinearColor::*)(int32)const, &FLinearColor::Component,
				                           TArray<FString>{"Index"}))
				.Function("GetClamped", BINDING_FUNCTION(&FLinearColor::GetClamped,
				                                         TArray<FString>{"InMin", "InMax"}, 0.0f, 1.0f))
				.Function("Equals", BINDING_FUNCTION(&FLinearColor::Equals,
				                                     TArray<FString>{"ColorB", "Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("CopyWithNewOpacity", BINDING_FUNCTION(&FLinearColor::CopyWithNewOpacity,
				                                                 TArray<FString>{"NewOpacicty"}))
				.Function("MakeFromHSV8", BINDING_FUNCTION(&FLinearColor::MakeFromHSV8,
				                                           TArray<FString>{"H", "S", "V"}))
				.Function("MakeRandomColor", BINDING_FUNCTION(&FLinearColor::MakeRandomColor))
				.Function("MakeFromColorTemperature", BINDING_FUNCTION(&FLinearColor::MakeFromColorTemperature,
				                                                       TArray<FString>{"Temp"}))
				.Function("Dist", BINDING_FUNCTION(&FLinearColor::Dist,
				                                   TArray<FString>{"V1", "V2"}))
				.Function("EvaluateBezier", BINDING_FUNCTION(&FLinearColor::EvaluateBezier,
				                                             TArray<FString>{"ControlPoints", "NumPoints",
				                                             "OutPoints"}))
				.Function("LinearRGBToHSV", BINDING_FUNCTION(&FLinearColor::LinearRGBToHSV))
				.Function("HSVToLinearRGB", BINDING_FUNCTION(&FLinearColor::HSVToLinearRGB))
				.Function("LerpUsingHSV", BINDING_FUNCTION(&FLinearColor::LerpUsingHSV,
				                                           TArray<FString>{"From", "To", "Progress"}))
				.Function("QuantizeRound", BINDING_FUNCTION(&FLinearColor::QuantizeRound))
				.Function("QuantizeFloor", BINDING_FUNCTION(&FLinearColor::QuantizeFloor))
				.Function("ToFColorSRGB", BINDING_FUNCTION(&FLinearColor::ToFColorSRGB))
				.Function("ToFColor", BINDING_FUNCTION(&FLinearColor::ToFColor,
				                                       TArray<FString>{"bSRGB"}))
				.Function("Desaturate", BINDING_FUNCTION(&FLinearColor::Desaturate,
				                                         TArray<FString>{"Desaturation"}))
				.Function("GetLuminance", BINDING_FUNCTION(&FLinearColor::GetLuminance))
				.Function("GetMax", BINDING_FUNCTION(&FLinearColor::GetMax))
				.Function("IsAlmostBlack", BINDING_FUNCTION(&FLinearColor::IsAlmostBlack))
				.Function("GetMin", BINDING_FUNCTION(&FLinearColor::GetMin))
				.Function("ToString", BINDING_FUNCTION(&FLinearColor::ToString,
				                                       EFunctionInteract::New))
				.Function("InitFromString", BINDING_FUNCTION(&FLinearColor::InitFromString,
				                                             TArray<FString>{"InSourceString"}));
		}
	};

	[[maybe_unused]] FRegisterLinearColor RegisterLinearColor;
}
