#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/Property/TPropertyBuilder.inl"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/BindingMacro.h"

BINDING_REFLECTION_CLASS(UClass)

struct FRegisterClass
{
	FRegisterClass()
	{
		TBindingClassBuilder<UClass>(NAMESPACE_LIBRARY)
			.Property("ClassDefaultObject", BINDING_READONLY_PROPERTY(&UClass::ClassDefaultObject))
			.Function("GetDefaultObject", BINDING_OVERLOAD(UObject*(UClass::*)(bool)const, &UClass::GetDefaultObject),
			          {"bCreateIfNeeded"})
			.Register();
	}
};

static FRegisterClass RegisterClass;
