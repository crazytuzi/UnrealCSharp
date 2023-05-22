#pragma once

#if WITH_EDITOR
#include "IDirectoryWatcher.h"
#endif

class FMixinGenerator
{
public:
	static UNREALCSHARPCORE_API void Generator();

#if WITH_EDITOR
	static UNREALCSHARPCORE_API void Generator(const TArray<FFileChangeData>& FileChangeData);
#endif
};
