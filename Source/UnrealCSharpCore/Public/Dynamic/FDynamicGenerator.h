#pragma once

#if WITH_EDITOR
#include "IDirectoryWatcher.h"
#include "EDynamicType.h"
#include "mono/metadata/object-forward.h"
#endif

class UNREALCSHARPCORE_API FDynamicGenerator
{
public:
	static void Generator();

	static bool IsDynamicClass(const UClass* InClass);

	static bool IsDynamicStruct(const UScriptStruct* InScriptStruct);

	static bool IsDynamicEnum(const UEnum* InEnum);

	static FString GetNameSpace(const UClass* InClass);

	static FString GetNameSpace(const UScriptStruct* InScriptStruct);

	static FString GetNameSpace(const UEnum* InEnum);

#if WITH_EDITOR
	static void CodeAnalysisGenerator();

	static void SetCodeAnalysisDynamicFilesMap();

	static FString GetDynamicFile(const UClass* InClass);

	static FString GetDynamicFile(const FString& InName);

	static FString GetDynamicNormalizeFile(const UClass* InClass);

	static void Generator(const TArray<FFileChangeData>& InFileChangeData);

	static void OnPrePIEEnded(const bool bIsSimulating);

	static bool IsFullGenerator();

	static EDynamicType GetDynamicType(const FString& InFile, MonoClass*& OutMonoClass);

private:
	static bool bIsFullGenerator;

	static TMap<FString, FString> CodeAnalysisDynamicFilesMap;
#endif
};
