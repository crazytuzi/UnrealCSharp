#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterSoftClassPtr
{
	static void RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InClass)
	{
		const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InClass);

		const auto SoftClassPtr = new TSoftClassPtr<UObject>(FoundClass);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftClassPtr<UObject>>(InMonoObject, SoftClassPtr);
	}

	static bool IdenticalImplementation(const FGarbageCollectionHandle InA, const FGarbageCollectionHandle InB)
	{
		if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(InA))
		{
			if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(InB))
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
			(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TSoftClassPtr<UObject>>(
				InGarbageCollectionHandle);
		});
	}

	static void GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
	{
		const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(
			InGarbageCollectionHandle);

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
	}

	static void LoadSynchronousImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject** OutValue)
	{
		const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(
			InGarbageCollectionHandle);

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Multi->LoadSynchronous());
	}

	FRegisterSoftClassPtr()
	{
		FClassBuilder(TEXT("SoftClassPtr"), NAMESPACE_LIBRARY)
			.Function("Register", RegisterImplementation)
			.Function("Identical", IdenticalImplementation)
			.Function("UnRegister", UnRegisterImplementation)
			.Function("Get", GetImplementation)
			.Function("LoadSynchronous", LoadSynchronousImplementation)
			.Register();
	}
};

static FRegisterSoftClassPtr RegisterSoftClassPtr;
