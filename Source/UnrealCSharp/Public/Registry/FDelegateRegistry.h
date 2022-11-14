#pragma once

#include "mono/metadata/object-forward.h"

class FDelegateRegistry
{
public:
	FDelegateRegistry();

	~FDelegateRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	template <typename T>
	auto GetDelegate(const void* InAddress);

	template <typename T>
	auto GetObject(const T* InDelegate);

	bool AddReference(void* InAddress, void* InDelegate, MonoObject* InMonoObject);

	template <typename T>
	auto RemoveReference(const MonoObject* InMonoObject);

	template <typename T>
	auto RemoveReference(const void* InAddress);

private:
	TMap<MonoObject*, void*> MonoObject2DelegateMap;

	TMap<void*, MonoObject*> Delegate2MonoObjectMap;

	TMap<void*, void*> Address2DelegateMap;
};

#include "FDelegateRegistry.inl"
