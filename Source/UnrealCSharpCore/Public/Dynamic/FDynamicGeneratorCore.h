#pragma once

#include "mono/metadata/details/reflection-types.h"

class FDynamicGeneratorCore
{
public:
	static UPackage* GetOuter();

	static FString GetClassNameSpace();

	static void SetPropertyFlags(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetPropertyMetaData(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo);
	
	static void SetFunctionFlags(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetFunctionMetaData(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetClassMetaData(UClass* InClass, MonoCustomAttrInfo* InMonoCustomAttrInfo);

#if WITH_EDITOR
	static TArray<FString> GetDynamic(const FString& InFile, const FString& InField);
#endif

private:
	static bool AttrsHasAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, const FString& InAttributeName);

	static MonoObject* AttrsGetAttr(MonoCustomAttrInfo* Info, MonoClass* Attr_klass);

	static MonoProperty* AttrGetProperty(MonoClass* InMonoClass, const char* InName);

	static MonoObject* PropertyGetValue(MonoProperty* InMonoCustomProp, void* obj, void** params, MonoObject** exc);

	static char* StringToUTF8(MonoString* InMonoString);
};
