#include "Domain/InternalCall/FClassImplementation.h"
#include "Binding/Class/TClassBuilder.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"

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
	if (const auto FoundClass = Cast<UClass>(FCSharpEnvironment::GetEnvironment()->GetObject(InMonoObject)))
	{
		const auto Object = FoundClass->ClassDefaultObject;

		if (const auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Object))
		{
			*OutValue = FoundMonoObject;
		}
		else
		{
			const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				FTypeBridge::GetClassNameSpace(UObject::StaticClass()),
				FTypeBridge::GetFullClass(UObject::StaticClass()));

			*OutValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment()->AddObjectReference(Object, *OutValue);
		}
	}
}

void FClassImplementation::Class_GetDefaultObjectImplementation(const MonoObject* InMonoObject,
                                                                const bool bCreateIfNeeded, MonoObject** OutValue)
{
	if (const auto FoundClass = Cast<UClass>(FCSharpEnvironment::GetEnvironment()->GetObject(InMonoObject)))
	{
		const auto Object = FoundClass->GetDefaultObject(bCreateIfNeeded);

		if (const auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Object))
		{
			*OutValue = FoundMonoObject;
		}
		else
		{
			const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				FTypeBridge::GetClassNameSpace(UObject::StaticClass()),
				FTypeBridge::GetFullClass(UObject::StaticClass()));

			*OutValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment()->AddObjectReference(Object, *OutValue);
		}
	}
}
