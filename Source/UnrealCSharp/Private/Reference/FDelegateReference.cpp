#include "Reference/FDelegateReference.h"

FDelegateReference::~FDelegateReference()
{
	FCSharpEnvironment::GetEnvironment().RemoveDelegateReference(GarbageCollectionHandle);
}
