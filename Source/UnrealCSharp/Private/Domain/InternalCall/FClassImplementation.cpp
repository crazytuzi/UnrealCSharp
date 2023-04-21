#include "Domain/InternalCall/FClassImplementation.h"
#include "Binding/Class/TClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterUClass
{
	FRegisterUClass()
	{
		TClassBuilder<UClass>(NAMESPACE_LIBRARY)
			.Property("ClassDefaultObject",
			          static_cast<void*>(FClassImplementation::Class_GetClassDefaultObjectImplementation), nullptr)
			.Function("GetDefaultObject",
			          static_cast<void*>(FClassImplementation::Class_GetDefaultObjectImplementation))
			.Register();
	}
};

static FRegisterUClass RegisterUClass;

void FClassImplementation::Class_GetClassDefaultObjectImplementation(const MonoObject* InMonoObject,
                                                                     MonoObject** OutValue)
{
	if (const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InMonoObject))
	{
		const auto Object = FoundClass->ClassDefaultObject;

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Object);
	}
}

void FClassImplementation::Class_GetDefaultObjectImplementation(const MonoObject* InMonoObject,
                                                                const bool bCreateIfNeeded, MonoObject** OutValue)
{
	if (const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InMonoObject))
	{
		const auto Object = FoundClass->GetDefaultObject(bCreateIfNeeded);

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Object);
	}
}
