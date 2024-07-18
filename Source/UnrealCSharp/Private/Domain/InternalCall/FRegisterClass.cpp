#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/Property/TPropertyBuilder.inl"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/BindingMacro.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

namespace
{
	struct FRegisterClass
	{
		FRegisterClass()
		{
			TBindingClassBuilder<UClass>(NAMESPACE_LIBRARY,
			                             {
				                             []()
				                             {
					                             return FUnrealCSharpFunctionLibrary::GetFullClass(
						                             UClass::StaticClass());
				                             }
			                             })
				.Property("ClassDefaultObject", BINDING_READONLY_PROPERTY(&UClass::ClassDefaultObject))
				.Function("GetDefaultObject", BINDING_OVERLOAD(UObject*(UClass::*)(bool)const,
				                                               &UClass::GetDefaultObject,
				                                               TArray<FString>{"bCreateIfNeeded"}, true));
		}
	};

	FRegisterClass RegisterClass;
}
