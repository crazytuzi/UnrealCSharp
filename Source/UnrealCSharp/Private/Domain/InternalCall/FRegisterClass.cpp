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
		static void RemoveFunctionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                         const FGarbageCollectionHandle InName)
		{
			if (const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(
				InGarbageCollectionHandle))
			{
				const auto Name = FCSharpEnvironment::GetEnvironment().GetString<FName>(InName);

				if (const auto Function = FoundClass->FindFunctionByName(*Name))
				{
					if (Function->IsRooted())
					{
						Function->RemoveFromRoot();
					}
					else
					{
						Function->MarkAsGarbage();
					}

					FoundClass->RemoveFunctionFromFunctionMap(Function);
				}
			}
		}

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
#if UE_U_CLASS_CLASS_DEFAULT_OBJECT
				.Property("ClassDefaultObject", BINDING_READONLY_PROPERTY(&UClass::ClassDefaultObject))
#endif
				.Function("GetDefaultObject", BINDING_OVERLOAD(UObject*(UClass::*)(bool)const,
				                                               &UClass::GetDefaultObject,
				                                               TArray<FString>{"bCreateIfNeeded"}, true))
				.Function("RemoveFunction", RemoveFunctionImplementation);
		}
	};

	[[maybe_unused]] FRegisterClass RegisterClass;
}
