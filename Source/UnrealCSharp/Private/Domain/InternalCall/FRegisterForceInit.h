#pragma once

#include "Binding/Enum/TBindingEnumBuilder.inl"
#include "Macro/BindingMacro.h"

BINDING_ENUM(EForceInit)

struct FRegisterForceInit
{
	FRegisterForceInit()
	{
		TBindingEnumBuilder<EForceInit, false>()
			.Enumerator("ForceInit", EForceInit::ForceInit)
			.Enumerator("ForceInitToZero", EForceInit::ForceInitToZero);
	}
};

[[maybe_unused]] static FRegisterForceInit RegisterForceInit;
