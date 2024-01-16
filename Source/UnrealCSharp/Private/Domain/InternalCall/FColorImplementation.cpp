#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterColor
{
	FRegisterColor()
	{
		TReflectionClassBuilder<FColor>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FColor, uint8, uint8, uint8, uint8),
			             {"R", "G", "B", "A"})
			.Constructor(BINDING_CONSTRUCTOR(FColor, uint32),
			             {"InColor"})
			.Property("White", BINDING_PROPERTY(&FColor::White))
			.Property("Black", BINDING_PROPERTY(&FColor::Black))
			.Property("Transparent", BINDING_PROPERTY(&FColor::Transparent))
			.Property("Red", BINDING_PROPERTY(&FColor::Red))
			.Property("Green", BINDING_PROPERTY(&FColor::Green))
			.Property("Blue", BINDING_PROPERTY(&FColor::Blue))
			.Property("Yellow", BINDING_PROPERTY(&FColor::Yellow))
			.Property("Cyan", BINDING_PROPERTY(&FColor::Cyan))
			.Property("Magenta", BINDING_PROPERTY(&FColor::Magenta))
			.Property("Orange", BINDING_PROPERTY(&FColor::Orange))
			.Property("Purple", BINDING_PROPERTY(&FColor::Purple))
			.Property("Turquoise", BINDING_PROPERTY(&FColor::Turquoise))
			.Property("Silver", BINDING_PROPERTY(&FColor::Silver))
			.Property("Emerald", BINDING_PROPERTY(&FColor::Emerald))
			// @TODO
			// DWColor
			.Function("FromRGBE", BINDING_FUNCTION(&FColor::FromRGBE))
			.Function("FromHex", BINDING_FUNCTION(&FColor::FromHex),
			          {"HexString"})
			.Function("MakeRandomColor", BINDING_FUNCTION(&FColor::MakeRandomColor))
			.Function("MakeRedToGreenColorFromScalar", BINDING_FUNCTION(&FColor::MakeRedToGreenColorFromScalar),
			          {"Scalar"})
			.Function("MakeFromColorTemperature", BINDING_FUNCTION(&FColor::MakeFromColorTemperature),
			          {"Temp"})
			.Function("QuantizeUNormFloatTo8", BINDING_FUNCTION(&FColor::QuantizeUNormFloatTo8),
			          {"UnitFloat"})
			.Function("QuantizeUNormFloatTo16", BINDING_FUNCTION(&FColor::QuantizeUNormFloatTo16),
			          {"UnitFloat"})
			.Function("DequantizeUNorm8ToFloat", BINDING_FUNCTION(&FColor::DequantizeUNorm8ToFloat),
			          {"Value8"})
			.Function("DequantizeUNorm16ToFloat", BINDING_FUNCTION(&FColor::DequantizeUNorm16ToFloat),
			          {"Value16"})
			.Function("Requantize10to8", BINDING_FUNCTION(&FColor::Requantize10to8),
			          {"Value10"})
			.Function("Requantize16to8", BINDING_FUNCTION(&FColor::Requantize16to8),
			          {"Value16"})
			.Function("MakeRequantizeFrom1010102", BINDING_FUNCTION(&FColor::MakeRequantizeFrom1010102),
			          {"R", "G", "B", "A"})
			.Function("WithAlpha", BINDING_FUNCTION(&FColor::WithAlpha),
			          {"Alpha"})
			.Function("ReinterpretAsLinear", BINDING_FUNCTION(&FColor::ReinterpretAsLinear))
			.Function("ToHex", BINDING_FUNCTION(&FColor::ToHex))
			.Function("ToString", BINDING_FUNCTION(&FColor::ToString))
			.Function("InitFromString", BINDING_FUNCTION(&FColor::InitFromString),
			          {"InSourceString"})
			.Function("ToPackedARGB", BINDING_FUNCTION(&FColor::ToPackedARGB))
			.Function("ToPackedABGR", BINDING_FUNCTION(&FColor::ToPackedABGR))
			.Function("ToPackedRGBA", BINDING_FUNCTION(&FColor::ToPackedRGBA))
			.Function("ToPackedBGRA", BINDING_FUNCTION(&FColor::ToPackedBGRA))
			.Register();
	}
};

static FRegisterColor RegisterColor;
