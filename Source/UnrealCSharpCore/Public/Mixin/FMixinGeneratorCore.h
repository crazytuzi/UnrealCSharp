#pragma once

#include "mono/metadata/details/reflection-types.h"

class FMixinGeneratorCore
{
public:
	static UPackage* GetOuter();

	static FString GetClassNameSpace();

	static void SetPropertyFlags(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetFunctionFlags(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo);

#if WITH_EDITOR
	static TArray<FString> GetMixin(const FString& InFile, const FString& InField);
#endif

private:
	static bool AttrsHasAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, const FString& InAttributeName);
};
