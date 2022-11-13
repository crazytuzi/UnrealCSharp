#include "Registry/FDelegateRegistry.h"

FDelegateRegistry::FDelegateRegistry()
{
	Initialize();
}

FDelegateRegistry::~FDelegateRegistry()
{
	Deinitialize();
}

void FDelegateRegistry::Initialize()
{
}

void FDelegateRegistry::Deinitialize()
{
	// @TODO
}

bool FDelegateRegistry::AddReference(void* InAddress, void* InDelegate, MonoObject* InMonoObject)
{
	Address2DelegateMap.Emplace(InAddress, InDelegate);

	Delegate2MonoObjectMap.Emplace(InDelegate, InMonoObject);

	MonoObject2DelegateMap.Emplace(InMonoObject, InDelegate);

	return true;
}
