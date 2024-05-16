#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/Property/TPropertyBuilder.inl"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/BindingMacro.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

#ifdef _MSC_VER
#pragma warning (push)

#pragma warning (disable: 5103)
#endif

struct FRegisterClass
{
	FRegisterClass()
	{
		TBindingClassBuilder<UClass>(NAMESPACE_LIBRARY,
		                             {
			                             []()
			                             {
				                             return FUnrealCSharpFunctionLibrary::GetFullClass(UClass::StaticClass());
			                             }
		                             })
			.Property("ClassDefaultObject", BINDING_READONLY_PROPERTY(&UClass::ClassDefaultObject))
			.Function("GetDefaultObject", BINDING_OVERLOAD(UObject*(UClass::*)(bool)const, &UClass::GetDefaultObject,
			                                               TArray<FString>{"bCreateIfNeeded"}, true));
	}
};

static FRegisterClass RegisterClass;

#ifdef _MSC_VER
#pragma warning (pop)
#endif
