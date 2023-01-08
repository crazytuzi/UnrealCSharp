#include "Registry/FObjectRegistry.h"

FObjectRegistry::FObjectRegistry()
{
	Initialize();
}

FObjectRegistry::~FObjectRegistry()
{
	Deinitialize();
}

void FObjectRegistry::Initialize()
{
}

void FObjectRegistry::Deinitialize()
{
	Object2MonoObjectMap.Empty();

	MonoObject2ObjectMap.Empty();
}

void* FObjectRegistry::GetAddress(const MonoObject* InMonoObject)
{
	if (const auto FoundObject = MonoObject2ObjectMap.Find(InMonoObject))
	{
		return *FoundObject;
	}

	return nullptr;
}

void* FObjectRegistry::GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct)
{
	if (const auto FoundObject = MonoObject2ObjectMap.Find(InMonoObject))
	{
		InStruct = (*FoundObject)->GetClass();

		return *FoundObject;
	}

	return nullptr;
}

MonoObject* FObjectRegistry::GetObject(const UObject* InObject)
{
	const auto FoundMonoObject = Object2MonoObjectMap.Find(InObject);

	return FoundMonoObject != nullptr ? *FoundMonoObject : nullptr;
}

UObject* FObjectRegistry::GetObject(const MonoObject* InMonoObject)
{
	const auto FoundObject = MonoObject2ObjectMap.Find(InMonoObject);

	return FoundObject != nullptr ? *FoundObject : nullptr;
}

bool FObjectRegistry::AddReference(UObject* InObject, MonoObject* InMonoObject)
{
	Object2MonoObjectMap.Emplace(InObject, InMonoObject);

	MonoObject2ObjectMap.Emplace(InMonoObject, InObject);

	return true;
}

bool FObjectRegistry::RemoveReference(const UObject* InObject)
{
	if (const auto FoundMonoObject = Object2MonoObjectMap.Find(InObject))
	{
		Object2MonoObjectMap.Remove(InObject);

		MonoObject2ObjectMap.Remove(*FoundMonoObject);
	}

	return true;
}

bool FObjectRegistry::RemoveReference(const MonoObject* InMonoObject)
{
	if (const auto FoundObject = MonoObject2ObjectMap.Find(InMonoObject))
	{
		MonoObject2ObjectMap.Remove(InMonoObject);

		Object2MonoObjectMap.Remove(*FoundObject);
	}

	return true;
}
