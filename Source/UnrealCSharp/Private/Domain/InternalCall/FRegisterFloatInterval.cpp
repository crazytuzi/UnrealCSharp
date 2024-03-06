#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterFloatInterval
{
	FRegisterFloatInterval()
	{
		TBindingClassBuilder<FFloatInterval>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FFloatInterval, float, float),
			             {"InMin", "InMax"})
			.Function("Size", BINDING_FUNCTION(&FFloatInterval::Size))
			.Function("IsValid", BINDING_FUNCTION(&FFloatInterval::IsValid))
			.Function("Contains", BINDING_FUNCTION(&FFloatInterval::Contains),
			          {"Element"})
			.Function("Expand", BINDING_FUNCTION(&FFloatInterval::Expand),
			          {"ExpandAmount"})
			.Function("Include", BINDING_FUNCTION(&FFloatInterval::Include),
			          {"X"})
			.Function("Interpolate", BINDING_FUNCTION(&FFloatInterval::Interpolate),
			          {"Alpha"})
			.Register();
	}
};

static FRegisterFloatInterval RegisterFloatInterval;
