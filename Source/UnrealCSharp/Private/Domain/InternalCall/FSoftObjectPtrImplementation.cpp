#include "Domain/InternalCall/FSoftObjectPtrImplementation.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterSoftObjectPtr
{
	FRegisterSoftObjectPtr()
	{
		FClassBuilder(TEXT("SoftObjectPtr"), NAMESPACE_LIBRARY)
			.Function("Register", FSoftObjectPtrImplementation::SoftObjectPtr_RegisterImplementation)
			.Function("UnRegister", FSoftObjectPtrImplementation::SoftObjectPtr_UnRegisterImplementation)
			.Function("Get", FSoftObjectPtrImplementation::SoftObjectPtr_GetImplementation)
			.Register();
	}
};

static FRegisterSoftObjectPtr RegisterSoftObjectPtr;

void FSoftObjectPtrImplementation::SoftObjectPtr_RegisterImplementation(MonoObject* InMonoObject,
                                                                        const MonoObject* InObject)
{
	const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

	const auto SoftObjectPtr = new TSoftObjectPtr<UObject>(FoundObject);

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftObjectPtr<UObject>>(InMonoObject, SoftObjectPtr);
}

void FSoftObjectPtrImplementation::SoftObjectPtr_UnRegisterImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TSoftObjectPtr<UObject>>(
			InGarbageCollectionHandle);
	});
}

void FSoftObjectPtrImplementation::SoftObjectPtr_GetImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftObjectPtr<
		UObject>>(InGarbageCollectionHandle);

	*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
}
