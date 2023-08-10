#include "Domain/InternalCall/FWeakObjectPtrImplementation.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterWeakObjectPtr
{
	FRegisterWeakObjectPtr()
	{
		FClassBuilder(TEXT("WeakObjectPtr"), NAMESPACE_LIBRARY)
			.Function("Register", FWeakObjectPtrImplementation::WeakObjectPtr_RegisterImplementation)
			.Function("UnRegister", FWeakObjectPtrImplementation::WeakObjectPtr_UnRegisterImplementation)
			.Function("Get", FWeakObjectPtrImplementation::WeakObjectPtr_GetImplementation)
			.Register();
	}
};

static FRegisterWeakObjectPtr RegisterWeakObjectPtr;

void FWeakObjectPtrImplementation::WeakObjectPtr_RegisterImplementation(MonoObject* InMonoObject,
                                                                        const MonoObject* InObject)
{
	const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

	const auto WeakObjectPtr = new TWeakObjectPtr<UObject>(FoundObject);

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TWeakObjectPtr<UObject>>(InMonoObject, WeakObjectPtr);
}

void FWeakObjectPtrImplementation::WeakObjectPtr_UnRegisterImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TWeakObjectPtr<UObject>>(
			InGarbageCollectionHandle);
	});
}

void FWeakObjectPtrImplementation::WeakObjectPtr_GetImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<
		UObject>>(InGarbageCollectionHandle);

	*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
}
