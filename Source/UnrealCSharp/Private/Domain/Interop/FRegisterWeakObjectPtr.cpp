#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterWeakObjectPtr
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject,
		                                   const IManagedHandle InObject, const IManagedHandle InManagedType)
		{
			const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

			const auto WeakObjectPtr = new TWeakObjectPtr<UObject>(FoundObject);

			const auto Class = FReflectionRegistry::Get().GetClass(InManagedType);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TWeakObjectPtr<UObject>, true, false>(
				Class, InManagedObject, WeakObjectPtr);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<UObject>>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<UObject>>(InB))
				{
					return *FoundA == *FoundB ? 1 : 0;
				}
			}

			return 0;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TWeakObjectPtr<UObject>>(
					InManagedHandle);
			});
		}

		static IManagedHandle GetImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment()
				.GetMulti<TWeakObjectPtr<UObject>>(InManagedHandle);

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
