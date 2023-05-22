#pragma once

#include "mono/metadata/details/reflection-types.h"

class FMixinGeneratorCore
{
public:
	static void SetPropertyFlags(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo);

private:
	static bool AttrsHasAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, const FString& InAttributeName);
};
