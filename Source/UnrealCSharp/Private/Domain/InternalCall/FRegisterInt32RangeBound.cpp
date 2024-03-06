#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterInt32RangeBound
{
	FRegisterInt32RangeBound()
	{
		TBindingClassBuilder<FInt32RangeBound>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FInt32RangeBound, const int32&),
			             {"InValue"})
			.Function("GetValue", BINDING_FUNCTION(&FInt32RangeBound::GetValue))
			.Function("SetValue", BINDING_FUNCTION(&FInt32RangeBound::SetValue),
			          {"NewValue"})
			.Function("IsClosed", BINDING_FUNCTION(&FInt32RangeBound::IsClosed))
			.Function("IsExclusive", BINDING_FUNCTION(&FInt32RangeBound::IsExclusive))
			.Function("IsInclusive", BINDING_FUNCTION(&FInt32RangeBound::IsInclusive))
			.Function("IsOpen", BINDING_FUNCTION(&FInt32RangeBound::IsOpen))
			.Function("Exclusive", BINDING_FUNCTION(&FInt32RangeBound::Exclusive),
			          {"Value"})
			.Function("Inclusive", BINDING_FUNCTION(&FInt32RangeBound::Inclusive),
			          {"Value"})
			.Function("Open", BINDING_FUNCTION(&FInt32RangeBound::Open))
			.Function("FlipInclusion", BINDING_FUNCTION(&FInt32RangeBound::FlipInclusion),
			          {"Bound"})
			.Function("MaxLower", BINDING_FUNCTION(&FInt32RangeBound::MaxLower),
			          {"A", "B"})
			.Function("MaxUpper", BINDING_FUNCTION(&FInt32RangeBound::MaxUpper),
			          {"A", "B"})
			.Function("MinLower", BINDING_FUNCTION(&FInt32RangeBound::MinLower),
			          {"A", "B"})
			.Function("MinUpper", BINDING_FUNCTION(&FInt32RangeBound::MinUpper),
			          {"A", "B"})
			.Register();
	}
};

static FRegisterInt32RangeBound RegisterInt32RangeBound;
