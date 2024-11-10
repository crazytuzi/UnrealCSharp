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

	static void SetCodeAnalysisDynamicFilesMap();

	static FString GetDynamicFile(const UStruct* InStruct);

	static FString GetDynamicFile(const UEnum* InEnum);

	static FString GetDynamicFile(const FString& InName);

	static FString GetDynamicNormalizeFile(const UStruct* InStruct);

	static FString GetDynamicNormalizeFile(const UEnum* InEnum);

	static void Generator(const TArray<FFileChangeData>& FileChangeData);

	static void OnPrePIEEnded();

	static bool IsFullGenerator();

private:
	static bool bIsFullGenerator;

	static TMap<FString, FString> CodeAnalysisDynamicFilesMap;
#endif
};
