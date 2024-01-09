#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterSubclassOf
{
	static void RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InClass)
	{
		const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InClass);

		const auto SubclassOf = new TSubclassOf<UObject>(FoundClass);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>>(InMonoObject, SubclassOf);
	}

	static bool IdenticalImplementation(const FGarbageCollectionHandle InA, const FGarbageCollectionHandle InB)
	{
		if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(InA))
		{
			if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(InB))
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
			(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TSubclassOf<
				UObject>>(InGarbageCollectionHandle);
		});
	}

	static void GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                              MonoObject** OutValue)
	{
		const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(
			InGarbageCollectionHandle);

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
	}

	FRegisterSubclassOf()
	{
		FClassBuilder(TEXT("SubclassOf"), NAMESPACE_LIBRARY)
			.Function("Register", RegisterImplementation)
			.Function("Identical", IdenticalImplementation)
			.Function("UnRegister", UnRegisterImplementation)
			.Function("Get", GetImplementation)
			.Register();
	}
};

static FRegisterSubclassOf RegisterSubclassOf;
