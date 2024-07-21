#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

namespace
{
	struct FRegisterInt32RangeBound
	{
		FRegisterInt32RangeBound()
		{
			TBindingClassBuilder<FInt32RangeBound>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FInt32RangeBound, const int32&),
				             TArray<FString>{"InValue"})
				.Function("GetValue", BINDING_FUNCTION(&FInt32RangeBound::GetValue))
				.Function("SetValue", BINDING_FUNCTION(&FInt32RangeBound::SetValue,
				                                       TArray<FString>{"NewValue"}))
				.Function("IsClosed", BINDING_FUNCTION(&FInt32RangeBound::IsClosed))
				.Function("IsExclusive", BINDING_FUNCTION(&FInt32RangeBound::IsExclusive))
				.Function("IsInclusive", BINDING_FUNCTION(&FInt32RangeBound::IsInclusive))
				.Function("IsOpen", BINDING_FUNCTION(&FInt32RangeBound::IsOpen))
				.Function("Exclusive", BINDING_FUNCTION(&FInt32RangeBound::Exclusive,
				                                        TArray<FString>{"Value"}))
				.Function("Inclusive", BINDING_FUNCTION(&FInt32RangeBound::Inclusive,
				                                        TArray<FString>{"Value"}))
				.Function("Open", BINDING_FUNCTION(&FInt32RangeBound::Open))
				.Function("FlipInclusion", BINDING_FUNCTION(&FInt32RangeBound::FlipInclusion,
				                                            TArray<FString>{"Bound"}))
				.Function("MaxLower", BINDING_FUNCTION(&FInt32RangeBound::MaxLower,
				                                       TArray<FString>{"A", "B"}))
				.Function("MaxUpper", BINDING_FUNCTION(&FInt32RangeBound::MaxUpper,
				                                       TArray<FString>{"A", "B"}))
				.Function("MinLower", BINDING_FUNCTION(&FInt32RangeBound::MinLower,
				                                       TArray<FString>{"A", "B"}))
				.Function("MinUpper", BINDING_FUNCTION(&FInt32RangeBound::MinUpper,
				                                       TArray<FString>{"A", "B"}));
		}
	};

	FRegisterInt32RangeBound RegisterInt32RangeBound;
}
