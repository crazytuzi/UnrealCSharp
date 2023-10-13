#include "Reference/FBindingReference.h"
#include "Environment/FCSharpEnvironment.h"

FBindingReference::~FBindingReference()
{
	(void)FCSharpEnvironment::GetEnvironment().RemoveBindingReference(GarbageCollectionHandle);
}
