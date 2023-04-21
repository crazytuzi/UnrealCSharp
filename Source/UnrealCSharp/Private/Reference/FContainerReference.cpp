#include "Reference/FContainerReference.h"

FContainerReference::~FContainerReference()
{
	FCSharpEnvironment::GetEnvironment().RemoveContainerReference(GarbageCollectionHandle);
}
