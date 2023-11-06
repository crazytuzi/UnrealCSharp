#pragma once

#if WITH_EDITOR
#include "IDirectoryWatcher.h"
#endif

class FDynamicGenerator
{
public:
	static UNREALCSHARPCORE_API void Generator();

#if WITH_EDITOR
	static UNREALCSHARPCORE_API void CodeAnalysisGenerator();
#endif

#if WITH_EDITOR
	static UNREALCSHARPCORE_API void Generator(const TArray<FFileChangeData>& FileChangeData);
#endif
};
