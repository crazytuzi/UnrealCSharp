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
	static auto NewRef(MonoObject* InMonoObject, const mono_bool bPinned)
	{
		return FDomain::GCHandle_New_V2(InMonoObject, bPinned);
	}

	static auto NewWeakRef(MonoObject* InMonoObject, const mono_bool bTrackResurrection)
	{
		return FDomain::GCHandle_New_WeakRef_V2(InMonoObject, bTrackResurrection);
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

	static auto MonoObject2GarbageCollectionHandle(MonoObject* InMonoObject,
	                                               MonoProperty* InMonoProperty) -> T*
	{
		return static_cast<T*>(FMonoDomain::Object_Unbox(
			FMonoDomain::Property_Get_Value(InMonoProperty, InMonoObject, nullptr, nullptr)));
	}

	static auto MonoObject2GarbageCollectionHandle(MonoObject* InMonoObject)
	{
		const auto FoundProperty = FMonoDomain::Class_Get_Property_From_Name(
			FMonoDomain::Object_Get_Class(InMonoObject), PROPERTY_GARBAGE_COLLECTION_HANDLE);

		return FoundProperty != nullptr
			       ? MonoObject2GarbageCollectionHandle(InMonoObject, FoundProperty)
			       : nullptr;
	}

private:
	T Handle;
};
