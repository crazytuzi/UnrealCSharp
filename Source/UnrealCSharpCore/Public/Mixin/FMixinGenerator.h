#pragma once

#include "IDirectoryWatcher.h"
#include "mono/metadata/object-forward.h"

class FMixinGenerator
{
public:
	static UNREALCSHARPCORE_API void Generator();

	static UNREALCSHARPCORE_API void Generator(const TArray<FFileChangeData>& FileChangeData);

private:
	static void Generator(MonoClass* InMonoClass);

	static void GeneratorProperty(MonoClass* InMonoClass, class UCSharpGeneratedClass* InClass);

	static void GeneratorFunction(MonoClass* InMonoClass, class UCSharpGeneratedClass* InClass);
};
