#pragma once

#include "Reflection/Delegate/FDelegateBaseHelper.h"
#include "TAddress.inl"
#include "TValueMapping.inl"
#include "mono/metadata/object-forward.h"

class FDelegateRegistry
{
private:
	struct FDelegateAddress : TAddress<FDelegateBaseHelper*>
	{
		using TAddress::TAddress;
	};

public:
	FDelegateRegistry();

	~FDelegateRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	template <typename T>
	auto GetDelegate(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	MonoObject* GetObject(const void* InAddress);

	bool AddReference(void* InAddress, void* InDelegate, MonoObject* InMonoObject);

	bool AddReference(const FGarbageCollectionHandle& InOwner, void* InAddress, void* InDelegate,
	                  MonoObject* InMonoObject);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	TValueMapping<void*, FDelegateAddress>::GarbageCollectionHandle2Value GarbageCollectionHandle2DelegateAddress;

	TValueMapping<void*, FDelegateAddress>::Value2GarbageCollectionHandle Address2GarbageCollectionHandle;
};

#include "FDelegateRegistry.inl"
