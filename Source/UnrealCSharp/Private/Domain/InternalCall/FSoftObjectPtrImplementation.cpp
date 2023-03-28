#include "Domain/InternalCall/FSoftObjectPtrImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

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

	*OutValue = FCSharpEnvironment::GetEnvironment()->Bind(Multi.Get());
}
