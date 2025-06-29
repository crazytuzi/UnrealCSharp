#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/Property/TPropertyBuilder.inl"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/BindingMacro.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "UEVersion.h"

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
#if UE_CLASS_CLASS_DEFAULT_OBJECT
				.Property("ClassDefaultObject", BINDING_READONLY_PROPERTY(&UClass::ClassDefaultObject))
#endif
				.Function("GetDefaultObject", BINDING_OVERLOAD(UObject*(UClass::*)(bool)const,
				                                               &UClass::GetDefaultObject,
				                                               TArray<FString>{"bCreateIfNeeded"}, true));
		}
	};

	[[maybe_unused]] FRegisterClass RegisterClass;
}
