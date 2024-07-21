#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

namespace
{
	struct FRegisterColor
	{
		FRegisterColor()
		{
			TBindingClassBuilder<FColor>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FColor, uint8, uint8, uint8, uint8),
				             TArray<FString>{"R", "G", "B", "A"})
				.Constructor(BINDING_CONSTRUCTOR(FColor, uint32),
				             TArray<FString>{"InColor"})
				.Property("White", BINDING_READONLY_PROPERTY(&FColor::White))
				.Property("Black", BINDING_READONLY_PROPERTY(&FColor::Black))
				.Property("Transparent", BINDING_READONLY_PROPERTY(&FColor::Transparent))
				.Property("Red", BINDING_READONLY_PROPERTY(&FColor::Red))
				.Property("Green", BINDING_READONLY_PROPERTY(&FColor::Green))
				.Property("Blue", BINDING_READONLY_PROPERTY(&FColor::Blue))
				.Property("Yellow", BINDING_READONLY_PROPERTY(&FColor::Yellow))
				.Property("Cyan", BINDING_READONLY_PROPERTY(&FColor::Cyan))
				.Property("Magenta", BINDING_READONLY_PROPERTY(&FColor::Magenta))
				.Property("Orange", BINDING_READONLY_PROPERTY(&FColor::Orange))
				.Property("Purple", BINDING_READONLY_PROPERTY(&FColor::Purple))
				.Property("Turquoise", BINDING_READONLY_PROPERTY(&FColor::Turquoise))
				.Property("Silver", BINDING_READONLY_PROPERTY(&FColor::Silver))
				.Property("Emerald", BINDING_READONLY_PROPERTY(&FColor::Emerald))
				// @TODO
				// DWColor
				.Function("FromRGBE", BINDING_FUNCTION(&FColor::FromRGBE))
				.Function("FromHex", BINDING_FUNCTION(&FColor::FromHex,
				                                      TArray<FString>{"HexString"}))
				.Function("MakeRandomColor", BINDING_FUNCTION(&FColor::MakeRandomColor))
				.Function("MakeRedToGreenColorFromScalar", BINDING_FUNCTION(&FColor::MakeRedToGreenColorFromScalar,
				                                                            TArray<FString>{"Scalar"}))
				.Function("MakeFromColorTemperature", BINDING_FUNCTION(&FColor::MakeFromColorTemperature,
				                                                       TArray<FString>{"Temp"}))
				.Function("QuantizeUNormFloatTo8", BINDING_FUNCTION(&FColor::QuantizeUNormFloatTo8,
				                                                    TArray<FString>{"UnitFloat"}))
				.Function("QuantizeUNormFloatTo16", BINDING_FUNCTION(&FColor::QuantizeUNormFloatTo16,
				                                                     TArray<FString>{"UnitFloat"}))
				.Function("DequantizeUNorm8ToFloat", BINDING_FUNCTION(&FColor::DequantizeUNorm8ToFloat,
				                                                      TArray<FString>{"Value8"}))
				.Function("DequantizeUNorm16ToFloat", BINDING_FUNCTION(&FColor::DequantizeUNorm16ToFloat,
				                                                       TArray<FString>{"Value16"}))
				.Function("Requantize10to8", BINDING_FUNCTION(&FColor::Requantize10to8,
				                                              TArray<FString>{"Value10"}))
				.Function("Requantize16to8", BINDING_FUNCTION(&FColor::Requantize16to8,
				                                              TArray<FString>{"Value16"}))
				.Function("MakeRequantizeFrom1010102", BINDING_FUNCTION(&FColor::MakeRequantizeFrom1010102,
				                                                        TArray<FString>{"R", "G", "B", "A"}))
				.Function("WithAlpha", BINDING_FUNCTION(&FColor::WithAlpha,
				                                        TArray<FString>{"Alpha"}))
				.Function("ReinterpretAsLinear", BINDING_FUNCTION(&FColor::ReinterpretAsLinear))
				.Function("ToHex", BINDING_FUNCTION(&FColor::ToHex))
				.Function("ToString", BINDING_FUNCTION(&FColor::ToString,
				                                       EFunctionInteract::New))
				.Function("InitFromString", BINDING_FUNCTION(&FColor::InitFromString,
				                                             TArray<FString>{"InSourceString"}))
				.Function("ToPackedARGB", BINDING_FUNCTION(&FColor::ToPackedARGB))
				.Function("ToPackedABGR", BINDING_FUNCTION(&FColor::ToPackedABGR))
				.Function("ToPackedRGBA", BINDING_FUNCTION(&FColor::ToPackedRGBA))
				.Function("ToPackedBGRA", BINDING_FUNCTION(&FColor::ToPackedBGRA));
		}
	};

	FRegisterColor RegisterColor;
}
