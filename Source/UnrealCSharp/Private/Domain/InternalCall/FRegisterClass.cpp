#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/Property/TPropertyBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/BindingMacro.h"
#include "Macro/NamespaceMacro.h"

BINDING_REFLECTION_CLASS(UClass)

struct FRegisterClass
{
	static MonoObject* GetDefaultObjectImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  const bool bCreateIfNeeded)
	{
		if (const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InGarbageCollectionHandle))
		{
			const auto Object = FoundClass->GetDefaultObject(bCreateIfNeeded);

			return FCSharpEnvironment::GetEnvironment().Bind(Object);
		}

		return nullptr;
	}

	FRegisterClass()
	{
		TReflectionClassBuilder<UClass>(NAMESPACE_LIBRARY)
			.Property("ClassDefaultObject", BINDING_READONLY_PROPERTY(&UClass::ClassDefaultObject))
			.Function("GetDefaultObject", GetDefaultObjectImplementation)
			.Register();
	}
};

static FRegisterClass RegisterClass;
