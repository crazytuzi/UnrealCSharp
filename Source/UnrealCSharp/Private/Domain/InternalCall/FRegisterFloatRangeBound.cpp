#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterFloatRangeBound
{
	FRegisterFloatRangeBound()
	{
		TReflectionClassBuilder<FFloatRangeBound>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FFloatRangeBound, const float&),
			             {"InValue"})
			.Function("GetValue", BINDING_FUNCTION(&FFloatRangeBound::GetValue))
			.Function("SetValue", BINDING_FUNCTION(&FFloatRangeBound::SetValue),
			          {"NewValue"})
			.Function("IsClosed", BINDING_FUNCTION(&FFloatRangeBound::IsClosed))
			.Function("IsExclusive", BINDING_FUNCTION(&FFloatRangeBound::IsExclusive))
			.Function("IsInclusive", BINDING_FUNCTION(&FFloatRangeBound::IsInclusive))
			.Function("IsOpen", BINDING_FUNCTION(&FFloatRangeBound::IsOpen))
			.Function("Exclusive", BINDING_FUNCTION(&FFloatRangeBound::Exclusive),
			          {"Value"})
			.Function("Inclusive", BINDING_FUNCTION(&FFloatRangeBound::Inclusive),
			          {"Value"})
			.Function("Open", BINDING_FUNCTION(&FFloatRangeBound::Open))
			.Function("FlipInclusion", BINDING_FUNCTION(&FFloatRangeBound::FlipInclusion),
			          {"Bound"})
			.Function("MaxLower", BINDING_FUNCTION(&FFloatRangeBound::MaxLower),
			          {"A", "B"})
			.Function("MaxUpper", BINDING_FUNCTION(&FFloatRangeBound::MaxUpper),
			          {"A", "B"})
			.Function("MinLower", BINDING_FUNCTION(&FFloatRangeBound::MinLower),
			          {"A", "B"})
			.Function("MinUpper", BINDING_FUNCTION(&FFloatRangeBound::MinUpper),
			          {"A", "B"})
			.Register();
	}
};

static FRegisterFloatRangeBound RegisterFloatRangeBound;
