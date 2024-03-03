#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterInt32Range
{
	FRegisterInt32Range()
	{
		TBindingClassBuilder<FInt32Range>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FInt32Range, const int32&),
			             {"A"})
			.Constructor(BINDING_CONSTRUCTOR(FInt32Range, const int32&, const int32&),
			             {"A", "B"})
			.Constructor(BINDING_CONSTRUCTOR(FInt32Range, const FInt32RangeBound&, const FInt32RangeBound&),
			             {"InLowerBound", "InUpperBound"})
			// @TODO
			// Adjoins
			// Conjoins
			// Contains
			// Contiguous
			// GetLowerBound
			// SetLowerBound
			.Function("SetLowerBoundValue", BINDING_FUNCTION(&FInt32Range::SetLowerBoundValue),
			          {"NewLowerBoundValue"})
			.Function("GetLowerBoundValue", BINDING_FUNCTION(&FInt32Range::GetLowerBoundValue))
			// @TODO
			// GetUpperBound
			// SetUpperBound
			.Function("SetUpperBoundValue", BINDING_FUNCTION(&FInt32Range::SetUpperBoundValue),
			          {"NewUpperBoundValue"})
			.Function("GetUpperBoundValue", BINDING_FUNCTION(&FInt32Range::GetUpperBoundValue))
			.Function("HasLowerBound", BINDING_FUNCTION(&FInt32Range::HasLowerBound))
			.Function("HasUpperBound", BINDING_FUNCTION(&FInt32Range::HasUpperBound))
			.Function("IsDegenerate", BINDING_FUNCTION(&FInt32Range::IsDegenerate))
			.Function("IsEmpty", BINDING_FUNCTION(&FInt32Range::IsEmpty))
			// @TODO
			// Overlaps
			.Function("Split", BINDING_FUNCTION(&FInt32Range::Split),
			          {"Element"})
			// @TODO
			// Difference
			// Hull
			// Intersection
			.Function("Union", BINDING_FUNCTION(&FInt32Range::Union),
			          {"X", "Y"})
			.Function("All", BINDING_FUNCTION(&FInt32Range::All))
			.Function("AtLeast", BINDING_FUNCTION(&FInt32Range::AtLeast),
			          {"Value"})
			.Function("AtMost", BINDING_FUNCTION(&FInt32Range::AtMost),
			          {"Value"})
			.Function("Empty", BINDING_FUNCTION(&FInt32Range::Empty))
			// @TODO
			// Exclusive
			// GreaterThan
			// Inclusive
			// LessThan
			.Register();
	}
};

static FRegisterInt32Range RegisterInt32Range;
