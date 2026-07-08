#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterLazyObjectPtr
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject, const IManagedHandle InObject,
		                                   const IManagedHandle InManagedType)
		{
			const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

			const auto LazyObjectPtr = new TLazyObjectPtr<UObject>(FoundObject);

			const auto Class = FReflectionRegistry::Get().GetClass(InManagedType);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TLazyObjectPtr<UObject>, true, false>(
				Class, InManagedObject, LazyObjectPtr);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetMulti<TLazyObjectPtr<UObject>>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetMulti<TLazyObjectPtr<UObject>>(InB))
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
				(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TLazyObjectPtr<UObject>>(
					InManagedHandle);
			});
		}

		static IManagedHandle GetImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TLazyObjectPtr<
				UObject>>(InManagedHandle);

			return FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
		}

		FRegisterLazyObjectPtr()
		{
			FClassBuilder(TEXT("TLazyObjectPtr"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("Get", GetImplementation);
		}
	};

	[[maybe_unused]] FRegisterLazyObjectPtr RegisterLazyObjectPtr;
}
