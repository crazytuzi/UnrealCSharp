#pragma once

#include "mono/metadata/object-forward.h"

class FBindingRegistry
{
public:
	template <typename T>
	auto GetBinding(const MonoObject* InMonoObject);

public:
	bool AddReference(void* InBinding, MonoObject* InMonoObject);

private:
	TMap<MonoObject*, void*> MonoObject2BindingMap;
};

#include "FBindingRegistry.inl"
