#include "Domain/InternalCall/FSoftClassPtrImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterSoftClassPtr
{
	FRegisterSoftClassPtr()
	{
		FBindingClassBuilder(TEXT("SoftClassPtr"), NAMESPACE_LIBRARY)
			.Function("Register",
			          static_cast<void*>(FSoftClassPtrImplementation::SoftClassPtr_RegisterImplementation))
			.Function("UnRegister",
			          static_cast<void*>(FSoftClassPtrImplementation::SoftClassPtr_UnRegisterImplementation))
			.Function("Get",
			          static_cast<void*>(FSoftClassPtrImplementation::SoftClassPtr_GetImplementation))
			.Register();
	}
};

static FRegisterSoftClassPtr RegisterSoftClassPtr;

void FSoftClassPtrImplementation::SoftClassPtr_RegisterImplementation(MonoObject* InMonoObject,
                                                                      const MonoObject* InClass)
{
	const auto FoundClass = FCSharpEnvironment::GetEnvironment()->GetObject<UClass>(InClass);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TSoftClassPtr<UObject>>(InMonoObject, FoundClass);
}

void FSoftClassPtrImplementation::SoftClassPtr_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TSoftClassPtr<UObject>>(InMonoObject);
}

void FSoftClassPtrImplementation::SoftClassPtr_GetImplementation(const MonoObject* InMonoObject,
                                                                 MonoObject** OutValue)
{
	const auto Multi = FCSharpEnvironment::GetEnvironment()->GetMulti<TSoftClassPtr<UObject>>(InMonoObject);

	auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Multi.Get());

	if (FoundMonoObject == nullptr)
	{
		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(UClass::StaticClass()),
			FUnrealCSharpFunctionLibrary::GetFullClass(UClass::StaticClass()));

		FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

		// @TODO
		FCSharpEnvironment::GetEnvironment()->Bind(UClass::StaticClass(), false);

		FCSharpEnvironment::GetEnvironment()->AddObjectReference(Multi.Get(), FoundMonoObject);
	}

	*OutValue = FoundMonoObject;
}
