#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterLinearColor
{
	static FLinearColor MultipliesImplementation(const FLinearColor& In, const float Scalar)
	{
		return In * Scalar;
	}

	static FLinearColor DividesImplementation(const FLinearColor& In, const float Scalar)
	{
		return In / Scalar;
	}

	FRegisterLinearColor()
	{
		TReflectionClassBuilder<FLinearColor>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FLinearColor, EForceInit))
			.Constructor(BINDING_CONSTRUCTOR(FLinearColor, float, float, float, float),
			             {"InR", "InG", "InB", "InA"})
			.Constructor(BINDING_CONSTRUCTOR(FLinearColor, const FColor&),
			             {"Color"})
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
			.Function("FromSRGBColor", BINDING_FUNCTION(&FLinearColor::FromSRGBColor),
			          {"Color"})
			.Function("FromPow22Color", BINDING_FUNCTION(&FLinearColor::FromPow22Color),
			          {"Color"})
			.Function("Component",
			          BINDING_OVERLOAD(const float&(FLinearColor::*)(int32)const, &FLinearColor::Component),
			          {"Index"})
			.Function("GetClamped", BINDING_FUNCTION(&FLinearColor::GetClamped),
			          {"InMin", "InMax"})
			.Function("Equals", BINDING_FUNCTION(&FLinearColor::Equals),
			          {"ColorB", "Tolerance"})
			.Function("CopyWithNewOpacity", BINDING_FUNCTION(&FLinearColor::CopyWithNewOpacity),
			          {"NewOpacicty"})
			.Function("MakeFromHSV8", BINDING_FUNCTION(&FLinearColor::MakeFromHSV8),
			          {"H", "S", "V"})
			.Function("MakeRandomColor", BINDING_FUNCTION(&FLinearColor::MakeRandomColor))
			.Function("MakeFromColorTemperature", BINDING_FUNCTION(&FLinearColor::MakeFromColorTemperature),
			          {"Temp"})
			.Function("Dist", BINDING_FUNCTION(&FLinearColor::Dist),
			          {"V1", "V2"})
			.Function("EvaluateBezier", BINDING_FUNCTION(&FLinearColor::EvaluateBezier),
			          {"ControlPoints", "NumPoints", "OutPoints"})
			.Function("LinearRGBToHSV", BINDING_FUNCTION(&FLinearColor::LinearRGBToHSV))
			.Function("HSVToLinearRGB", BINDING_FUNCTION(&FLinearColor::HSVToLinearRGB))
			.Function("LerpUsingHSV", BINDING_FUNCTION(&FLinearColor::LerpUsingHSV),
			          {"From", "To", "Progress"})
			.Function("QuantizeRound", BINDING_FUNCTION(&FLinearColor::QuantizeRound))
			.Function("QuantizeFloor", BINDING_FUNCTION(&FLinearColor::QuantizeFloor))
			.Function("ToFColorSRGB", BINDING_FUNCTION(&FLinearColor::ToFColorSRGB))
			.Function("ToFColor", BINDING_FUNCTION(&FLinearColor::ToFColor),
			          {"bSRGB"})
			.Function("Desaturate", BINDING_FUNCTION(&FLinearColor::Desaturate),
			          {"Desaturation"})
			.Function("GetLuminance", BINDING_FUNCTION(&FLinearColor::GetLuminance))
			.Function("GetMax", BINDING_FUNCTION(&FLinearColor::GetMax))
			.Function("IsAlmostBlack", BINDING_FUNCTION(&FLinearColor::IsAlmostBlack))
			.Function("GetMin", BINDING_FUNCTION(&FLinearColor::GetMin))
			.Function("ToString", BINDING_FUNCTION(&FLinearColor::ToString),
			          {}, EFunctionInteract::New)
			.Function("InitFromString", BINDING_FUNCTION(&FLinearColor::InitFromString),
			          {"InSourceString"})
			.Register();
	}
};

static FRegisterLinearColor RegisterLinearColor;
