#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterSoftObjectPtr
	{
		static void RegisterImplementation(MonoObject* InMonoObject, const FGarbageCollectionHandle InObject)
		{
			const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

			const auto SoftObjectPtr = new TSoftObjectPtr<UObject>(FoundObject);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftObjectPtr<UObject>, true, false>(
				InMonoObject, SoftObjectPtr);
		}

		static bool IdenticalImplementation(const FGarbageCollectionHandle InA, const FGarbageCollectionHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftObjectPtr<UObject>>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftObjectPtr<UObject>>(InB))
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
				(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TSoftObjectPtr<UObject>>(
					InGarbageCollectionHandle);
			});
		}

		static MonoObject* GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment().
				GetMulti<TSoftObjectPtr<UObject>>(InGarbageCollectionHandle);

			return FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
		}

		static MonoObject* LoadSynchronousImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment().
				GetMulti<TSoftObjectPtr<UObject>>(InGarbageCollectionHandle);

			return FCSharpEnvironment::GetEnvironment().Bind(Multi->LoadSynchronous());
		}

		FRegisterSoftObjectPtr()
		{
			FClassBuilder(TEXT("TSoftObjectPtr"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("Get", GetImplementation)
				.Function("LoadSynchronous", LoadSynchronousImplementation);
		}
	};

	[[maybe_unused]] FRegisterSoftObjectPtr RegisterSoftObjectPtr;
}
