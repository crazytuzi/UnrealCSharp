#pragma once

#include "mono/metadata/object-forward.h"

class FTypeBridge
{
public:
	static EPropertyType GetPropertyType(MonoClass* InMonoClass);

	static MonoClass* GetMonoClass(const FProperty* InProperty);
};
