#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterInt32Interval
{
	FRegisterInt32Interval()
	{
		TBindingClassBuilder<FInt32Interval>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FInt32Interval, int32, int32),
			             {"InMin", "InMax"})
			.Function("Size", BINDING_FUNCTION(&FInt32Interval::Size))
			.Function("IsValid", BINDING_FUNCTION(&FInt32Interval::IsValid))
			.Function("Contains", BINDING_FUNCTION(&FInt32Interval::Contains),
			          {"Element"})
			.Function("Expand", BINDING_FUNCTION(&FInt32Interval::Expand),
			          {"ExpandAmount"})
			.Function("Include", BINDING_FUNCTION(&FInt32Interval::Include),
			          {"X"})
			.Function("Interpolate", BINDING_FUNCTION(&FInt32Interval::Interpolate),
			          {"Alpha"})
			.Register();
	}
};

static FRegisterInt32Interval RegisterInt32Interval;
