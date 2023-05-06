#pragma once

#include "mono/metadata/object.h"

class FTypeBridge
{
public:
	static FString UNREALCSHARPCORE_API GetPathName(MonoReflectionType* InReflectionType);
};
