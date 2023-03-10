#include "Domain/InternalCall/FSoftObjectPtrImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterSoftObjectPtr
{
	FRegisterSoftObjectPtr()
	{
		FBindingClassBuilder(TEXT("SoftObjectPtr"), NAMESPACE_LIBRARY)
			.Function("Register",
			          static_cast<void*>(FSoftObjectPtrImplementation::SoftObjectPtr_RegisterImplementation))
			.Function("UnRegister",
			          static_cast<void*>(FSoftObjectPtrImplementation::SoftObjectPtr_UnRegisterImplementation))
			.Function("Get",
			          static_cast<void*>(FSoftObjectPtrImplementation::SoftObjectPtr_GetImplementation))
			.Register();
	}
};

static FRegisterSoftObjectPtr RegisterSoftObjectPtr;

void FSoftObjectPtrImplementation::SoftObjectPtr_RegisterImplementation(MonoObject* InMonoObject,
                                                                        const MonoObject* InObject)
{
	const auto FoundObject = FCSharpEnvironment::GetEnvironment()->GetObject(InObject);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TSoftObjectPtr<UObject>>(InMonoObject, FoundObject);
}

void FSoftObjectPtrImplementation::SoftObjectPtr_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TSoftObjectPtr<UObject>>(InMonoObject);
}

void FSoftObjectPtrImplementation::SoftObjectPtr_GetImplementation(const MonoObject* InMonoObject,
                                                                   MonoObject** OutValue)
{
	const auto Multi = FCSharpEnvironment::GetEnvironment()->GetMulti<TSoftObjectPtr<UObject>>(InMonoObject);

	auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Multi.Get());

	if (FoundMonoObject == nullptr)
	{
		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(Multi->GetClass()),
			FUnrealCSharpFunctionLibrary::GetFullClass(Multi->GetClass()));

		FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

		FCSharpEnvironment::GetEnvironment()->Bind(Multi->GetClass(), false);

		FCSharpEnvironment::GetEnvironment()->AddObjectReference(Multi.Get(), FoundMonoObject);
	}

	*OutValue = FoundMonoObject;
}
