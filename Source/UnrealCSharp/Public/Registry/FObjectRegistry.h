#pragma once

#include "mono/metadata/object-forward.h"

class FObjectRegistry
{
public:
	FObjectRegistry();

	~FObjectRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	MonoObject* GetObject(const UObject* InObject);

	UObject* GetObject(const MonoObject* InMonoObject);

public:
	bool AddReference(UObject* InObject, MonoObject* InMonoObject);

	bool RemoveReference(const UObject* InObject);

	bool RemoveReference(const MonoObject* InMonoObject);

private:
	TMap<MonoObject*, UObject*> MonoObject2ObjectMap;

	TMap<UObject*, MonoObject*> Object2MonoObjectMap;
};
