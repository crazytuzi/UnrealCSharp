#pragma once

#if WITH_EDITOR
#include "IDirectoryWatcher.h"
#endif
#include "mono/metadata/object-forward.h"
#include "mono/metadata/details/reflection-types.h"

class FMixinGenerator
{
public:
	static UNREALCSHARPCORE_API void Generator();

#if WITH_EDITOR
	static UNREALCSHARPCORE_API void Generator(const TArray<FFileChangeData>& FileChangeData);
#endif

private:
	static void Generator(MonoClass* InMonoClass);

	static void GeneratorProperty(MonoClass* InMonoClass, class UClass* InClass);

	static void GeneratorFunction(MonoClass* InMonoClass, class UClass* InClass);

	static void SetPropertyFlags(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static bool AttrsHasAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, const FString& InAttributeName);
};
