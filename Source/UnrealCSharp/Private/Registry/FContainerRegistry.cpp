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

bool FContainerRegistry::AddReference(void* InContainer, MonoObject* InMonoObject)
{
	Container2MonoObjectMap.Emplace(InContainer, InMonoObject);

	MonoObject2ContainerMap.Emplace(InMonoObject, InContainer);

	return true;
}

bool FContainerRegistry::AddReference(void* InAddress, void* InContainer, MonoObject* InMonoObject)
{
	Address2ContainerMap.Emplace(InAddress, InContainer);

	Container2MonoObjectMap.Emplace(InContainer, InMonoObject);

	MonoObject2ContainerMap.Emplace(InMonoObject, InContainer);

	return true;
}
