#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

namespace
{
	struct FRegisterFloatRangeBound
	{
		FRegisterFloatRangeBound()
		{
			TBindingClassBuilder<FFloatRangeBound>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FFloatRangeBound, const float&),
				             TArray<FString>{"InValue"})
				.Function("GetValue", BINDING_FUNCTION(&FFloatRangeBound::GetValue))
				.Function("SetValue", BINDING_FUNCTION(&FFloatRangeBound::SetValue,
				                                       TArray<FString>{"NewValue"}))
				.Function("IsClosed", BINDING_FUNCTION(&FFloatRangeBound::IsClosed))
				.Function("IsExclusive", BINDING_FUNCTION(&FFloatRangeBound::IsExclusive))
				.Function("IsInclusive", BINDING_FUNCTION(&FFloatRangeBound::IsInclusive))
				.Function("IsOpen", BINDING_FUNCTION(&FFloatRangeBound::IsOpen))
				.Function("Exclusive", BINDING_FUNCTION(&FFloatRangeBound::Exclusive,
				                                        TArray<FString>{"Value"}))
				.Function("Inclusive", BINDING_FUNCTION(&FFloatRangeBound::Inclusive,
				                                        TArray<FString>{"Value"}))
				.Function("Open", BINDING_FUNCTION(&FFloatRangeBound::Open))
				.Function("FlipInclusion", BINDING_FUNCTION(&FFloatRangeBound::FlipInclusion,
				                                            TArray<FString>{"Bound"}))
				.Function("MaxLower", BINDING_FUNCTION(&FFloatRangeBound::MaxLower,
				                                       TArray<FString>{"A", "B"}))
				.Function("MaxUpper", BINDING_FUNCTION(&FFloatRangeBound::MaxUpper,
				                                       TArray<FString>{"A", "B"}))
				.Function("MinLower", BINDING_FUNCTION(&FFloatRangeBound::MinLower,
				                                       TArray<FString>{"A", "B"}))
				.Function("MinUpper", BINDING_FUNCTION(&FFloatRangeBound::MinUpper,
				                                       TArray<FString>{"A", "B"}));
		}
	};

	FRegisterFloatRangeBound RegisterFloatRangeBound;
}
