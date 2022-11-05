#include "Registry/FContainerRegistry.h"

FContainerRegistry::FContainerRegistry()
{
	Initialize();
}

FContainerRegistry::~FContainerRegistry()
{
	Deinitialize();
}

void FContainerRegistry::Initialize()
{
}

void FContainerRegistry::Deinitialize()
{
	// @TODO
}

bool FContainerRegistry::AddReference(void* InContainer, MonoObject* InMonoObject, bool bNeedFree)
{
	Container2MonoObjectMap.Emplace(InContainer, InMonoObject);

	MonoObject2ContainerMap.Emplace(InMonoObject, InContainer);

	return true;
}
