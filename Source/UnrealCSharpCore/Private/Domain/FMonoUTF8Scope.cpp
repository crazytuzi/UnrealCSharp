#include "Domain/FMonoUTF8Scope.h"
#include "Domain/FMonoDomain.h"

FMonoUTF8Scope::FMonoUTF8Scope(char* InString):
	String(InString)
{
}

FMonoUTF8Scope::~FMonoUTF8Scope()
{
	if (String != nullptr)
	{
		FMonoDomain::Free(String);
	}
}

FMonoUTF8Scope::operator const char*() const
{
	return String;
}
