#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

namespace
{
	struct FRegisterInt32Interval
	{
		FRegisterInt32Interval()
		{
			TBindingClassBuilder<FInt32Interval>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FInt32Interval, int32, int32),
				             TArray<FString>{"InMin", "InMax"})
				.Function("Size", BINDING_FUNCTION(&FInt32Interval::Size))
				.Function("IsValid", BINDING_FUNCTION(&FInt32Interval::IsValid))
				.Function("Contains", BINDING_FUNCTION(&FInt32Interval::Contains,
				                                       TArray<FString>{"Element"}))
				.Function("Expand", BINDING_FUNCTION(&FInt32Interval::Expand,
				                                     TArray<FString>{"ExpandAmount"}))
				.Function("Include", BINDING_FUNCTION(&FInt32Interval::Include,
				                                      TArray<FString>{"X"}))
				.Function("Interpolate", BINDING_FUNCTION(&FInt32Interval::Interpolate,
				                                          TArray<FString>{"Alpha"}));
		}
	};

	FRegisterInt32Interval RegisterInt32Interval;
}
