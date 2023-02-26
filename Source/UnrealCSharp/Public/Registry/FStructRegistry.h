#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.h"
#include "mono/metadata/object-forward.h"

class FStructRegistry
{
public:
	struct FStructAddress
	{
		void* Address;

		UScriptStruct* ScriptStruct;

		bool bNeedFree;
	};

public:
	FStructRegistry();

	~FStructRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	void* GetAddress(const MonoObject* InMonoObject);

	void* GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct);

	MonoObject* GetObject(const void* InStruct);

	void* GetStruct(const MonoObject* InMonoObject);

public:
	bool AddReference(UScriptStruct* InScriptStruct, void* InStruct, MonoObject* InMonoObject, bool bNeedFree = true);

	bool RemoveReference(const void* InStruct);

	bool RemoveReference(const MonoObject* InMonoObject);

private:
	TGarbageCollectionHandleMapping<FStructAddress> GarbageCollectionHandle2StructAddress;

	TMap<void*, FGarbageCollectionHandle> StructAddress2GarbageCollectionHandle;
};
