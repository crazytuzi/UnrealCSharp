#include "Domain/InternalCall/FClassImplementation.h"
#include "Binding/Class/TClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

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
	if (const auto FoundClass = FCSharpEnvironment::GetEnvironment()->GetObject<UClass>(InMonoObject))
	{
		const auto Object = FoundClass->ClassDefaultObject;

		auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Object);

		if (FoundMonoObject == nullptr)
		{
			const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(Object->GetClass()),
				FUnrealCSharpFunctionLibrary::GetFullClass(Object->GetClass()));

			FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment()->Bind(Object->GetClass(), false);

			FCSharpEnvironment::GetEnvironment()->AddObjectReference(Object, FoundMonoObject);
		}

		*OutValue = FoundMonoObject;
	}
}

void FClassImplementation::Class_GetDefaultObjectImplementation(const MonoObject* InMonoObject,
                                                                const bool bCreateIfNeeded, MonoObject** OutValue)
{
	if (const auto FoundClass = FCSharpEnvironment::GetEnvironment()->GetObject<UClass>(InMonoObject))
	{
		const auto Object = FoundClass->GetDefaultObject(bCreateIfNeeded);

		auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Object);

		if (FoundMonoObject == nullptr)
		{
			const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(Object->GetClass()),
				FUnrealCSharpFunctionLibrary::GetFullClass(Object->GetClass()));

			FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment()->Bind(Object->GetClass(), false);

			FCSharpEnvironment::GetEnvironment()->AddObjectReference(Object, FoundMonoObject);
		}

		*OutValue = FoundMonoObject;
	}
}
