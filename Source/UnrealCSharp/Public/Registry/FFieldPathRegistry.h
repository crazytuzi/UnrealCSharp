#pragma once

#include "UObject/FieldPath.h"
#include "TValueWrapper.inl"
#include "TValueMapping.inl"
#include "TOwnedValue.inl"
#include "Domain/Script/IManagedHandle.h"
#include "Reflection/FClassReflection.h"

class UNREALCSHARP_API FFieldPathRegistry
{
public:
	struct FFieldPathAddress : TValueWrapper<FFieldPath*>, TOwnedValue<FFieldPathAddress>
	{
		FFieldPathAddress(FFieldPath* InValue, const bool InNeedFree) :
			TValueWrapper<FFieldPath*>(InValue),
			TOwnedValue<FFieldPathAddress>(InNeedFree)
		{
		}

	private:
		template <typename>
		friend struct TOwnedValue;

		void FreeImplementation()
		{
			if (TValueWrapper<FFieldPath*>::Value != nullptr)
			{
				TValueWrapper<FFieldPath*>::Value->~FFieldPath();

				FMemory::Free(TValueWrapper<FFieldPath*>::Value);

				TValueWrapper<FFieldPath*>::Value = nullptr;
			}
		}
	};

	template <typename Key, typename Value>
	struct TFieldPathMapping : TValueMapping<Key, Value>
	{
		typedef typename TFieldPathMapping::FKey2ManagedHandle FAddress2ManagedHandle;
	};

	typedef TFieldPathMapping<void*, FFieldPathAddress> FFieldPathValueMapping;

	typedef TMap<FField*, IManagedHandle> FField2ManagedHandle;

	typedef TMap<IManagedHandle, FField*> FManagedHandle2Field;

public:
	FFieldPathRegistry();

	~FFieldPathRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	FFieldPath* GetFieldPath(const IManagedHandle InManagedHandle);

	IManagedHandle GetManagedHandle(const void* InAddress);

	FField* GetField(const IManagedHandle InManagedHandle);

	IManagedHandle GetFieldObject(FField* InField);

	template <auto IsNeedFree, auto IsMember>
	auto AddReference(FClassReflection* InClass, const IManagedHandle InManagedHandle, FFieldPath* InValue);

	bool RemoveReference(const IManagedHandle InManagedHandle);

private:
	FFieldPathValueMapping::FManagedHandle2Value ManagedHandle2Value;

	FFieldPathValueMapping::FAddress2ManagedHandle Address2ManagedHandle;

	FField2ManagedHandle Field2ManagedHandle;

	FManagedHandle2Field ManagedHandle2Field;
};

#include "FFieldPathRegistry.inl"
