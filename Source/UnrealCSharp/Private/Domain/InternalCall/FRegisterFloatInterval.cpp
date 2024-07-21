#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

namespace
{
	struct FRegisterFloatInterval
	{
		FRegisterFloatInterval()
		{
			TBindingClassBuilder<FFloatInterval>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FFloatInterval, float, float),
				             TArray<FString>{"InMin", "InMax"})
				.Function("Size", BINDING_FUNCTION(&FFloatInterval::Size))
				.Function("IsValid", BINDING_FUNCTION(&FFloatInterval::IsValid))
				.Function("Contains", BINDING_FUNCTION(&FFloatInterval::Contains,
				                                       TArray<FString>{"Element"}))
				.Function("Expand", BINDING_FUNCTION(&FFloatInterval::Expand,
				                                     TArray<FString>{"ExpandAmount"}))
				.Function("Include", BINDING_FUNCTION(&FFloatInterval::Include,
				                                      TArray<FString>{"X"}))
				.Function("Interpolate", BINDING_FUNCTION(&FFloatInterval::Interpolate,
				                                          TArray<FString>{"Alpha"}));
		}
	};

	FRegisterFloatInterval RegisterFloatInterval;
}
