#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterWeakObjectPtr
{
	static void RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InObject)
	{
		const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

		const auto WeakObjectPtr = new TWeakObjectPtr<UObject>(FoundObject);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TWeakObjectPtr<UObject>>(InMonoObject, WeakObjectPtr);
	}

	static bool IdenticalImplementation(const FGarbageCollectionHandle InA, const FGarbageCollectionHandle InB)
	{
		if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<UObject>>(InA))
		{
			if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<UObject>>(InB))
			{
				return *FoundA == *FoundB;
			}
		}

		return false;
	}

	static void UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
		{
			(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TWeakObjectPtr<UObject>>(
				InGarbageCollectionHandle);
		});
	}

	static void GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
	{
		const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<
			UObject>>(InGarbageCollectionHandle);

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
	}

	FRegisterWeakObjectPtr()
	{
		FClassBuilder(TEXT("WeakObjectPtr"), NAMESPACE_LIBRARY)
			.Function("Register", RegisterImplementation)
			.Function("Identical", IdenticalImplementation)
			.Function("UnRegister", UnRegisterImplementation)
			.Function("Get", GetImplementation)
			.Register();
	}
};

static FRegisterWeakObjectPtr RegisterWeakObjectPtr;
