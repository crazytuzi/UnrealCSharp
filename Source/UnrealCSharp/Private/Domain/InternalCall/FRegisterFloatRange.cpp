#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

namespace
{
	struct FRegisterFloatRange
	{
		FRegisterFloatRange()
		{
			TBindingClassBuilder<FFloatRange>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FFloatRange, const float&),
				             TArray<FString>{"A"})
				.Constructor(BINDING_CONSTRUCTOR(FFloatRange, const float&, const float&),
				             TArray<FString>{"A", "B"})
				.Constructor(BINDING_CONSTRUCTOR(FFloatRange, const FFloatRangeBound&, const FFloatRangeBound&),
				             TArray<FString>{"InLowerBound", "InUpperBound"})
				// @TODO
				// Adjoins
				// Conjoins
				// Contains
				// Contiguous
				// GetLowerBound
				// SetLowerBound
				.Function("SetLowerBoundValue", BINDING_FUNCTION(&FFloatRange::SetLowerBoundValue,
				                                                 TArray<FString>{"NewLowerBoundValue"}))
				.Function("GetLowerBoundValue", BINDING_FUNCTION(&FFloatRange::GetLowerBoundValue))
				// @TODO
				// GetUpperBound
				// SetUpperBound
				.Function("SetUpperBoundValue", BINDING_FUNCTION(&FFloatRange::SetUpperBoundValue,
				                                                 TArray<FString>{"NewUpperBoundValue"}))
				.Function("GetUpperBoundValue", BINDING_FUNCTION(&FFloatRange::GetUpperBoundValue))
				.Function("HasLowerBound", BINDING_FUNCTION(&FFloatRange::HasLowerBound))
				.Function("HasUpperBound", BINDING_FUNCTION(&FFloatRange::HasUpperBound))
				.Function("IsDegenerate", BINDING_FUNCTION(&FFloatRange::IsDegenerate))
				.Function("IsEmpty", BINDING_FUNCTION(&FFloatRange::IsEmpty))
				// @TODO
				// Overlaps
				.Function("Split", BINDING_FUNCTION(&FFloatRange::Split,
				                                    TArray<FString>{"Element"}))
				// @TODO
				// Difference
				// Hull
				// Intersection
				.Function("Union", BINDING_FUNCTION(&FFloatRange::Union,
				                                    TArray<FString>{"X", "Y"}))
				.Function("All", BINDING_FUNCTION(&FFloatRange::All))
				.Function("AtLeast", BINDING_FUNCTION(&FFloatRange::AtLeast,
				                                      TArray<FString>{"Value"}))
				.Function("AtMost", BINDING_FUNCTION(&FFloatRange::AtMost,
				                                     TArray<FString>{"Value"}))
				.Function("Empty", BINDING_FUNCTION(&FFloatRange::Empty));
				// @TODO
				// Exclusive
				// GreaterThan
				// Inclusive
				// LessThan
		}
	};

	FRegisterFloatRange RegisterFloatRange;
}
