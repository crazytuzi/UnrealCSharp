#include "Reference/FStructReference.h"
#include "Environment/FCSharpEnvironment.h"

FStructReference::~FStructReference()
{
	(void)FCSharpEnvironment::GetEnvironment().RemoveStructReference(GarbageCollectionHandle);
}
