#include "Domain/InternalCall/FMonoInternalCall.h"
#include "mono/metadata/loader.h"

void FMonoInternalCall::RegisterInternalCall(const char* InName, const void* InMethod)
{
	mono_add_internal_call(InName, InMethod);
}
