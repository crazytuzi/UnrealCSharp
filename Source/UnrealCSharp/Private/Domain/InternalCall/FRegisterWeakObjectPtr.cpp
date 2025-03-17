#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterWeakObjectPtr
	{
		static void RegisterImplementation(MonoObject* InMonoObject, const FGarbageCollectionHandle InObject)
		{
			const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

			const auto WeakObjectPtr = new TWeakObjectPtr<UObject>(FoundObject);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TWeakObjectPtr<UObject>, true, false>(
				InMonoObject, WeakObjectPtr);
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

		static MonoObject* GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment()
				.GetMulti<TWeakObjectPtr<UObject>>(InGarbageCollectionHandle);

			return FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
		}

		FRegisterWeakObjectPtr()
		{
			FClassBuilder(TEXT("TWeakObjectPtr"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("Get", GetImplementation);
		}
	};

	[[maybe_unused]] FRegisterWeakObjectPtr RegisterWeakObjectPtr;
}
