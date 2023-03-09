#include "Domain/InternalCall/FSubclassOfImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterSubclassOf
{
	FRegisterSubclassOf()
	{
		FBindingClassBuilder(TEXT("SubclassOf"), NAMESPACE_LIBRARY)
			.Function("Register",
			          static_cast<void*>(FSubclassOfImplementation::SubclassOf_RegisterImplementation))
			.Function("UnRegister",
			          static_cast<void*>(FSubclassOfImplementation::SubclassOf_UnRegisterImplementation))
			.Function("Get",
			          static_cast<void*>(FSubclassOfImplementation::SubclassOf_GetImplementation))
			.Register();
	}
};

static FRegisterSubclassOf RegisterSubclassOf;

void FSubclassOfImplementation::SubclassOf_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InClass)
{
	const auto FoundClass = FCSharpEnvironment::GetEnvironment()->GetObject<UClass>(InClass);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TSubclassOf<UObject>>(InMonoObject, FoundClass);
}

void FSubclassOfImplementation::SubclassOf_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TSubclassOf<UObject>>(InMonoObject);
}

void FSubclassOfImplementation::SubclassOf_GetImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Multi = FCSharpEnvironment::GetEnvironment()->GetMulti<TSubclassOf<UObject>>(InMonoObject);

	auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Multi);

	if (FoundMonoObject == nullptr)
	{
		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(UClass::StaticClass()),
			FUnrealCSharpFunctionLibrary::GetFullClass(UClass::StaticClass()));

		FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

		// @TODO	
		FCSharpEnvironment::GetEnvironment()->Bind(UClass::StaticClass(), false);

		FCSharpEnvironment::GetEnvironment()->AddObjectReference(Multi, FoundMonoObject);
	}

	*OutValue = FoundMonoObject;
}
