#include "Binding/Enum/TBindingEnumBuilder.inl"
#include "Macro/BindingMacro.h"

BINDING_ENGINE_ENUM(EForceInit)

struct FRegisterForceInit
{
	FRegisterForceInit()
	{
		TBindingEnumBuilder<EForceInit>()
			.Enumerator("ForceInit", EForceInit::ForceInit)
			.Enumerator("ForceInitToZero", EForceInit::ForceInitToZero)
			.Register();
	}
};

static FRegisterForceInit RegisterForceInit;
