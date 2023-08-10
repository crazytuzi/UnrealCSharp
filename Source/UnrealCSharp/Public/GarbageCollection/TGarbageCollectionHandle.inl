#pragma once

#include "mono/metadata/object-forward.h"
#include "Domain/FDomain.h"

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

	bool operator==(const TGarbageCollectionHandle& Other) const
	{
		return Handle == Other.Handle;
	}

	bool operator!=(const TGarbageCollectionHandle& Other) const
	{
		return !(*this == Other);
	}

	bool IsValid() const
	{
		return Handle != T();
	}

public:
	static TGarbageCollectionHandle NewRef(MonoObject* InMonoObject, const mono_bool bPinned)
	{
		return FDomain::GCHandle_New_V2(InMonoObject, bPinned);
	}

	static TGarbageCollectionHandle NewWeakRef(MonoObject* InMonoObject, const mono_bool bTrackResurrection)
	{
		return FDomain::GCHandle_New_WeakRef_V2(InMonoObject, bTrackResurrection);
	}

	static void Free(TGarbageCollectionHandle& InGarbageCollectionHandle, const bool bReset = true)
	{
		FDomain::GCHandle_Free_V2(InGarbageCollectionHandle);

		if (bReset)
		{
			InGarbageCollectionHandle = T();
		}
	}

private:
	T Handle;
};
