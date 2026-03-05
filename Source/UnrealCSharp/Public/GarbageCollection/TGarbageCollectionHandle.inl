#pragma once

#include "CoreMacro/PropertyMacro.h"
#include "Domain/FDomain.h"
#include "mono/metadata/object-forward.h"

template <typename T>
class TGarbageCollectionHandle
{
public:
	TGarbageCollectionHandle():
		Handle(T())
	{
	}

	TGarbageCollectionHandle(const T& InHandle):
		Handle(InHandle)
	{
	}

	operator T() const
	{
		return Handle;
	}

	operator MonoObject*() const
	{
		return FDomain::GCHandle_Get_Target_V2(Handle);
	}

	auto operator==(const TGarbageCollectionHandle& Other) const
	{
		return Handle == Other.Handle;
	}

	auto operator!=(const TGarbageCollectionHandle& Other) const
	{
		return !(*this == Other);
	}

	auto IsValid() const
	{
		return Handle != T();
	}

	static auto Zero() -> const TGarbageCollectionHandle&
	{
		static TGarbageCollectionHandle GarbageCollectionHandle;

		return GarbageCollectionHandle;
	}

public:
	static auto NewRef(const FClassReflection* InClass, MonoObject* InMonoObject, const mono_bool bPinned)
	{
		return InClass->NewGCHandle(InMonoObject, bPinned);
	}

	static auto NewWeakRef(const FClassReflection* InClass, MonoObject* InMonoObject,
	                       const mono_bool bTrackResurrection)
	{
		return InClass->NewWeakRefGCHandle(InMonoObject, bTrackResurrection);
	}

	template <auto IsReset>
	static auto Free(TGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		FDomain::GCHandle_Free_V2(InGarbageCollectionHandle);

		if constexpr (IsReset)
		{
			InGarbageCollectionHandle = T();
		}
	}

	static auto MonoObject2GarbageCollectionHandle(const FClassReflection* InClass, MonoObject* InMonoObject) -> T*
	{
		if (InClass != nullptr)
		{
			if (const auto FoundProperty = InClass->GetProperty(PROPERTY_GARBAGE_COLLECTION_HANDLE))
			{
				return static_cast<T*>(FDomain::Object_Unbox(FoundProperty->GetValue(InMonoObject, nullptr, nullptr)));
			}
		}

		return nullptr;
	}

private:
	T Handle;
};
