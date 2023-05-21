#include "Reference/FContainerReference.h"
#include "Environment/FCSharpEnvironment.h"

FContainerReference::~FContainerReference()
{
	(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference(
		static_cast<GarbageCollectionHandleType>(GarbageCollectionHandle));
}
