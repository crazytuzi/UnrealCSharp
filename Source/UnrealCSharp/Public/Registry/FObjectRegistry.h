#pragma once

#include "TValueMapping.inl"
#include "Reflection/FClassReflection.h"
#include "Domain/Script/IManagedHandle.h"

class UNREALCSHARP_API FObjectRegistry
{
private:
	template <typename Key>
	struct TObjectMapping : TValueMapping<Key>
	{
		typedef typename TObjectMapping::FKey2ManagedHandle FAddress2ManagedHandle;
	};

	typedef TObjectMapping<TWeakObjectPtr<const UObject>> FObjectMapping;

public:
	FObjectRegistry();

	~FObjectRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	void* GetAddress(const IManagedHandle InManagedHandle);

	void* GetAddress(const IManagedHandle InManagedHandle, UStruct*& InStruct);

	IManagedHandle GetObject(const UObject* InObject);

	UObject* GetObject(const IManagedHandle InManagedHandle);

	IManagedHandle GetManagedHandle(const UObject* InObject);

public:
	bool AddReference(const FClassReflection* InClass, UObject* InObject, const IManagedHandle InManagedHandle);

	bool RemoveReference(const UObject* InObject);

	bool RemoveReference(const IManagedHandle InManagedHandle);

private:
	FObjectMapping::FManagedHandle2Value ManagedHandle2Object;

	FObjectMapping::FAddress2ManagedHandle Object2ManagedHandle;
};
