#pragma once

#include "mono/metadata/object-forward.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"

struct FDelegateWrapper
{
	TWeakObjectPtr<UObject> Object;

	MonoObject* Delegate;

	FGarbageCollectionHandle GCHandle;
};

static bool operator==(const FDelegateWrapper& A, const FDelegateWrapper& B)
{
	return A.Object == B.Object && A.Delegate == B.Delegate;
}
