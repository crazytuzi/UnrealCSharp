#include "Reference/FDelegateReference.h"
#include "Environment/FCSharpEnvironment.h"

FDelegateReference::~FDelegateReference()
{
	(void)FCSharpEnvironment::GetEnvironment().RemoveDelegateReference(GarbageCollectionHandle);
}
