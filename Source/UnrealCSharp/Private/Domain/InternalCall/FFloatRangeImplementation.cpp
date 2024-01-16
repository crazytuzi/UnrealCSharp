#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterFloat
{
	FRegisterFloat()
	{
		TReflectionClassBuilder<FFloatRange>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FFloatRange, const float&),
			             {"A"})
			.Constructor(BINDING_CONSTRUCTOR(FFloatRange, const float&, const float&),
			             {"A", "B"})
			.Constructor(BINDING_CONSTRUCTOR(FFloatRange, const FFloatRangeBound&, const FFloatRangeBound&),
			             {"InLowerBound", "InUpperBound"})
			// @TODO
			// Adjoins
			// Conjoins
			// Contains
			// Contiguous
			// GetLowerBound
			// SetLowerBound
			.Function("SetLowerBoundValue", BINDING_FUNCTION(&FFloatRange::SetLowerBoundValue),
			          {"NewLowerBoundValue"})
			.Function("GetLowerBoundValue", BINDING_FUNCTION(&FFloatRange::GetLowerBoundValue))
			// @TODO
			// GetUpperBound
			// SetUpperBound
			.Function("SetUpperBoundValue", BINDING_FUNCTION(&FFloatRange::SetUpperBoundValue),
			          {"NewUpperBoundValue"})
			.Function("GetUpperBoundValue", BINDING_FUNCTION(&FFloatRange::GetUpperBoundValue))
			.Function("HasLowerBound", BINDING_FUNCTION(&FFloatRange::HasLowerBound))
			.Function("HasUpperBound", BINDING_FUNCTION(&FFloatRange::HasUpperBound))
			.Function("IsDegenerate", BINDING_FUNCTION(&FFloatRange::IsDegenerate))
			.Function("IsEmpty", BINDING_FUNCTION(&FFloatRange::IsEmpty))
			// @TODO
			// Overlaps
			.Function("Split", BINDING_FUNCTION(&FFloatRange::Split),
			          {"Element"})
			// @TODO
			// Difference
			// Hull
			// Intersection
			.Function("Union", BINDING_FUNCTION(&FFloatRange::Union),
			          {"X", "Y"})
			.Function("All", BINDING_FUNCTION(&FFloatRange::All))
			.Function("AtLeast", BINDING_FUNCTION(&FFloatRange::AtLeast),
			          {"Value"})
			.Function("AtMost", BINDING_FUNCTION(&FFloatRange::AtMost),
			          {"Value"})
			.Function("Empty", BINDING_FUNCTION(&FFloatRange::Empty))
			// @TODO
			// Exclusive
			// GreaterThan
			// Inclusive
			// LessThan
			.Register();
	}
};

static FRegisterFloat RegisterFloat;
