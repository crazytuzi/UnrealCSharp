#include "Registry/FBindingRegistry.h"

bool FBindingRegistry::AddReference(void* InBinding, MonoObject* InMonoObject)
{
	MonoObject2BindingMap.Emplace(InMonoObject, InBinding);

	return true;
}
