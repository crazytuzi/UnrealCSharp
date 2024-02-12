#pragma once

#if WITH_EDITOR
#include "IDirectoryWatcher.h"
#endif

class UNREALCSHARPCORE_API FDynamicGenerator
{
public:
	static void Generator();

#if WITH_EDITOR
	static void CodeAnalysisGenerator();

	static void Generator(const TArray<FFileChangeData>& FileChangeData);

	static void OnPrePIEEnded();

	static bool IsFullGenerator();

private:
	static bool bIsFullGenerator;
#endif
};
